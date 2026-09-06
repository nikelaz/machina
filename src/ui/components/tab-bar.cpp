/**
 * @file tab-bar.cpp
 * @brief Implementation of the tab bar components.
 */

#include "tab-bar.h"

#include "imgui.h"

#include <functional>

namespace ui::components {

/**
 * @brief Renders a tab bar wrapping the given tab items.
 */
void tabBar(std::string_view title, std::function<void()> body)
{
  if (ImGui::BeginTabBar(title.data()))
  {
    body();

    ImGui::EndTabBar();
  }
}

/**
 * @brief Renders a single tab item wrapping the given content.
 */
void tabBarItem(std::string_view title, std::function<void()> body)
{
  if (ImGui::BeginTabItem(title.data()))
  {
    body();

    ImGui::EndTabItem();
  }
}

} // namespace ui::components
