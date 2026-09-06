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
  ui::UISystem m_ui;
  std::atomic<std::shared_ptr<const AppState>> m_state;
  std::thread m_background_thread;
  std::atomic<bool> m_running;

  static GLFWwindow* createWindow();
  void destroyWindow();
  void backgroundWorker();
public:
  Application();
  ~Application();
  void run();
};
