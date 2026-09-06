/**
 * @file ui-system.cpp
 * @brief Implementation of the ImGui rendering system.
 */

#include "ui-system.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "app-state.h"

#include "ui/views/main-view.h"

namespace ui
{

/**
 * @brief Creates the ImGui context and initializes the GLFW/OpenGL3 backends.
 */
UISystem::UISystem(GLFWwindow* window)
  : m_window(window)
{
  createImGuiContext();
}

/**
 * @brief Shuts down the ImGui backends and destroys the context.
 */
UISystem::~UISystem()
{
  destroyImGuiContext();
}

/**
 * @brief Renders one full frame for the given state to the backbuffer.
 */
void UISystem::renderFrameToBackbuffer(const AppState& state)
{
  newFrame();
  prepareViewport();
  views::mainView(state);
  prepareBackbuffer();
}

/**
 * @brief Creates the ImGui context, GLFW and OpenGL3 backends and applies the theme.
 */
void UISystem::createImGuiContext()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
  setImGuiTheme();
}

/**
 * @brief Shuts down the OpenGL3 and GLFW backends and destroys the ImGui context.
 */
void UISystem::destroyImGuiContext()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

/**
 * @brief Starts a new ImGui frame via the OpenGL3 and GLFW backends.
 */
void UISystem::newFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

/**
 * @brief Renders ImGui draw data and presents the frame.
 *
 * Renders the accumulated ImGui draw data, clears and updates the viewport
 * to the current framebuffer size, and issues the buffer swap.
 */
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

/**
 * @brief Positions the next ImGui window to cover the full main viewport work area.
 */
void UISystem::prepareViewport()
{
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
}

/**
 * @brief Applies the application's custom dark ImGui theme (style and colors).
 */
void UISystem::setImGuiTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6f;
	style.WindowPadding = ImVec2(13.0f, 13.0f);
	style.WindowRounding = 0.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Right;
	style.ChildRounding = 3.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 3.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(13.0f, 7.0f);
	style.FrameRounding = 3.0f;
	style.FrameBorderSize = 1.0f;
	style.ItemSpacing = ImVec2(13.0f, 8.0f);
	style.ItemInnerSpacing = ImVec2(10.0f, 8.0f);
	style.CellPadding = ImVec2(8.0f, 6.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 5.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 20.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 3.0f;
	style.TabBorderSize = 1.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1254902f, 0.1254902f, 0.1254902f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1254902f, 0.1254902f, 0.1254902f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1254902f, 0.1254902f, 0.1254902f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1254902f, 0.1254902f, 0.1254902f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1254902f, 0.1254902f, 0.1254902f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3019608f, 0.3019608f, 0.3019608f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.34901962f, 0.34901962f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.47058824f, 0.84313726f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 0.47058824f, 0.84313726f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.32941177f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.3019608f, 0.3019608f, 0.3019608f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3019608f, 0.3019608f, 0.3019608f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.3019608f, 0.3019608f, 0.3019608f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.2509804f, 0.2509804f, 0.2509804f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.16862746f, 0.16862746f, 0.16862746f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.21568628f, 0.21568628f, 0.21568628f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.47058824f, 0.84313726f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.32941177f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.47058824f, 0.84313726f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.32941177f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882353f, 0.1882353f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.30980393f, 0.30980393f, 0.34901962f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.22745098f, 0.22745098f, 0.24705882f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.47058824f, 0.84313726f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.9f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.25882354f, 0.5882353f, 0.9764706f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}

} // namespace ui
