#include "ui-system.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "app-state.h"

#include "ui/views/main-view.h"

namespace ui
{

UISystem::UISystem(GLFWwindow* window)
  : m_window(window)
{
  createImGuiContext();
}

UISystem::~UISystem()
{
  destroyImGuiContext();
}

void UISystem::renderFrameToBackbuffer(const AppState& state)
{
  newFrame();
  prepareViewport();
  views::mainView(state);
  prepareBackbuffer();
}

void UISystem::createImGuiContext()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

void UISystem::destroyImGuiContext()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void UISystem::newFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void UISystem::prepareBackbuffer()
{
  ImGui::Render();

  int width;
  int height;
  glfwGetFramebufferSize(m_window, &width, &height);
  glViewport(0, 0, width, height);
  // TODO: This color should be a part of the pallete/theme
  glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UISystem::prepareViewport()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
}

} // namespace ui
