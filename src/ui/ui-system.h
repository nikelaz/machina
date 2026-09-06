#pragma once

struct GLFWwindow;

#include "app-state.h"

namespace ui
{

class UISystem
{
private:
  GLFWwindow* m_window;
  void createImGuiContext();
  void destroyImGuiContext();
  void newFrame();
  void prepareBackbuffer();
  void prepareViewport();
  void setImGuiTheme();
public:
  UISystem(GLFWwindow* window);
  ~UISystem();
  void renderFrameToBackbuffer(const AppState& state);
};

} // namespace ui
