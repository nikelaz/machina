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
#include "ui/icons.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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
 * @brief Decodes the embedded PNG icons and sets them as the window icon.
 *
 * The window manager picks the size closest to the icon slot it needs
 * (title bar, alt-tab switcher, task bar). Only supported on X11; on
 * Wayland the icon comes from the .desktop file instead.
 *
 * @param window Handle to the main GLFW window.
 */
static void setWindowIcon(GLFWwindow* window)
{
  GLFWimage images[ui::icons::embedded_icon_count];
  int count = 0;

  for (int i = 0; i < ui::icons::embedded_icon_count; ++i)
  {
    const ui::icons::EmbeddedIcon& icon = ui::icons::embedded_icons[i];

    int width = 0;
    int height = 0;
    int channels = 0;
    stbi_uc* pixels = stbi_load_from_memory(
      icon.data, static_cast<int>(icon.data_size), &width, &height, &channels, 4);
    if (!pixels)
    {
      std::fprintf(stderr, "failed to decode embedded %dpx icon\n", icon.size);
      continue;
    }

    images[count].width = width;
    images[count].height = height;
    images[count].pixels = pixels;
    ++count;
  }

  if (count > 0)
  {
    glfwSetWindowIcon(window, count, images);
  }

  for (int i = 0; i < count; ++i)
  {
    stbi_image_free(images[i].pixels);
  }
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
  const char* window_title = "Machina";

  GLFWwindow* window = glfwCreateWindow(
    window_width,
    window_height,
    "Machina",
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

  setWindowIcon(window);

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

