#pragma once

/**
 * @file ui-system.h
 * @brief ImGui rendering system tied to the main GLFW window.
 */

struct GLFWwindow;

#include "app-state.h"

namespace ui
{

/**
 * @brief Owns the ImGui context and renders AppState snapshots each frame.
 *
 * Wraps the ImGui + GLFW/OpenGL3 backend lifecycle and drives the main
 * view hierarchy. One frame is rendered per call to renderFrameToBackbuffer().
 */
class UISystem
{
private:
  GLFWwindow* m_window; ///< The GLFW window ImGui renders into.

  void createImGuiContext();
  void destroyImGuiContext();
  void newFrame();
  void prepareBackbuffer();
  void prepareViewport();
  void setImGuiTheme();
public:
  /**
   * @brief Creates the ImGui context and initializes the GLFW/OpenGL3 backends.
   *
   * @param window The GLFW window to render into (must have a current GL context).
   */
  UISystem(GLFWwindow* window);

  /**
   * @brief Shuts down the ImGui backends and destroys the context.
   */
  ~UISystem();

  /**
   * @brief Renders one full frame for the given state to the backbuffer.
   *
   * Starts a new ImGui frame, prepares the viewport, draws the main view
   * hierarchy and presents the result by rendering and swapping.
   *
   * @param state The application state snapshot to render.
   */
  void renderFrameToBackbuffer(const AppState& state);
};

} // namespace ui
