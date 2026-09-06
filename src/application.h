#include <GLFW/glfw3.h>

#include "ui/ui-system.h"
#include "app-state.h"

#include <thread>
#include <atomic>
#include <memory>

#pragma once

/**
 * @file application.h
 * @brief Top-level application lifecycle: window creation, main loop and
 *        background data collection.
 */

#include <GLFW/glfw3.h>

#include "ui/ui-system.h"
#include "app-state.h"

#include <thread>
#include <atomic>
#include <memory>

/**
 * @brief Owns the GLFW window, the UI system and the background worker.
 *
 * The application follows a producer/consumer model: a background thread
 * samples system information once per second and publishes immutable
 * AppState snapshots through an atomic shared_ptr, while the main thread
 * renders the latest snapshot to the window.
 */
class Application {
private:
  GLFWwindow* m_window = nullptr;                    ///< Handle to the main GLFW window.
  std::atomic<bool> m_running;                       ///< Signals the background worker to stop.
  std::atomic<std::shared_ptr<const AppState>> m_state; ///< Latest published state snapshot (read by the UI thread).
  std::thread m_background_thread;                   ///< Worker thread collecting system data.
  ui::UISystem m_ui;                                 ///< ImGui-based rendering system.

  static GLFWwindow* createWindow();
  void destroyWindow();
  void backgroundWorker();
public:
  /**
   * @brief Constructs the application and starts everything.
   *
   * Creates the GLFW window, initializes the UI system, spawns the
   * background worker thread and immediately enters the main loop.
   */
  Application();

  /**
   * @brief Destroys the window and stops the background worker.
   */
  ~Application();

  /**
   * @brief Runs the main loop until the window is closed.
   *
   * Polls window events and renders the most recent AppState snapshot to
   * the backbuffer each frame.
   */
  void run();
};
