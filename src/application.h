#include <GLFW/glfw3.h>

#include "ui/ui-system.h"
#include "app-state.h"

#include <thread>
#include <atomic>
#include <memory>

#pragma once

class Application {
private:
  GLFWwindow* m_window = nullptr;
  std::atomic<bool> m_running;
  std::atomic<std::shared_ptr<const AppState>> m_state;
  std::thread m_background_thread;
  ui::UISystem m_ui;

  static GLFWwindow* createWindow();
  void destroyWindow();
  void backgroundWorker();
public:
  Application();
  ~Application();
  void run();
};
