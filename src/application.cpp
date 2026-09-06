#include "application.h"

#include "process-reader.h"
#include "system-info.h"

#include <cstdio>
#include <vector>

Application::Application()
  : m_window(createWindow()),
    m_running(true),
    m_ui(m_window),
    m_background_thread(&Application::backgroundWorker, this)
{
}

void Application::backgroundWorker()
{
  using namespace std::chrono_literals;

  while (m_running)
  {
    auto new_state = std::make_shared<AppState>();

    auto systemInfoRes = getSystemInfo();

    if (systemInfoRes)
    {
      new_state->system_info = *systemInfoRes;
    }

    new_state->processes = process_reader::getProcesses();

    m_state.store(std::move(new_state));  // publish: atomic pointer swap, no data copied

    std::this_thread::sleep_for(1s);
  } 
}

Application::~Application()
{
  destroyWindow();
  m_background_thread.join();
}

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
  const int window_width = 500;
  const int window_height = 500;
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

void Application::destroyWindow()
{
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

void Application::run()
{
  m_running = true;

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

  m_running = false;
}

