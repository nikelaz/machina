/**
 * @file application.cpp
 * @brief Implementation of the Application lifecycle and background worker.
 */

#include "application.h"

#include "GLFW/glfw3.h"
#include "cpu-stats.h"
#include "memory-stats.h"
#include "process-reader.h"
#include "system-info.h"

#include <chrono>
#include <cstdio>
#include <expected>
#include <system_error>
#include <utility>
#include <vector>

Application::Application()
  : m_window(createWindow()),
    m_running(true),
    m_ui(m_window),
    m_background_thread(&Application::backgroundWorker, this)
{
  run();
}

/**
 * @brief Samples system information once per second until shutdown.
 *
 * Builds a fresh AppState snapshot on each iteration by reading system
 * information and the process list, then publishes it by atomically swapping
 * the shared pointer (no data is copied on the consuming side).
 */
void Application::backgroundWorker()
{
  using namespace std::chrono_literals;

  cpu_stats::ProcCpuStats cpu_stats_prev = cpu_stats::readProcCpuStats();
  cpu_stats::ProcCpuStats cpu_stats_current;

  while (m_running)
  {
    auto new_state = std::make_shared<AppState>();

    auto systemInfoRes = getSystemInfo();

    if (systemInfoRes)
    {
      new_state->system_info = *systemInfoRes;
    }

    new_state->processes = process_reader::getProcesses();

    cpu_stats_current = cpu_stats::readProcCpuStats();

    new_state->cpu_utilization = cpu_stats::getCpuUtilization(cpu_stats_prev, cpu_stats_current);
    cpu_stats_prev = cpu_stats_current;

    new_state->memory_info = memory_stats::getMemoryInfo(); 

    m_state.store(std::move(new_state));  // publish: atomic pointer swap, no data copied

    std::this_thread::sleep_for(1s);
  } 
}

/**
 * @brief Destroys the window and joins the background worker thread.
 */
Application::~Application()
{
  destroyWindow();
  m_running = false;
  m_background_thread.join();
}

/**
 * @brief Initializes GLFW and creates the main application window.
 *
 * Requests an OpenGL 3.0 context and enables vsync.
 *
 * @return Handle to the created window, or nullptr on failure (in which case
 *         GLFW is terminated before returning).
 */
GLFWwindow* Application::createWindow()
{
  // TODO: better error handling
  if (!glfwInit())
  {
    std::fprintf(stderr, "glfw init failed\n");
    return nullptr;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // TODO: Extract to some sort of app settings
  const int window_width = 450;
  const int window_height = 400;
  const char* window_title = "System Information";

  GLFWwindow* window = glfwCreateWindow(
    window_width,
    window_height,
    "System Information",
    nullptr,
    nullptr
  );

  // TODO: better error handling
  if (!window)
  {
    std::fprintf(stderr, "glfwCreateWindow failed\n");
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  return window;
}

/**
 * @brief Destroys the GLFW window and terminates GLFW.
 */
void Application::destroyWindow()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

/**
 * @brief Runs the main render loop until the window is closed.
 *
 * Each frame polls window events, loads the latest published AppState
 * snapshot (if any) and renders it to the backbuffer, then swaps buffers.
 */
void Application::run()
{
  while (!glfwWindowShouldClose(m_window))
  {
    glfwPollEvents();
    
    auto state = m_state.load();
    if (state)
    {
      m_ui.renderFrameToBackbuffer(*state);
    }

    glfwSwapBuffers(m_window);
  }
}

