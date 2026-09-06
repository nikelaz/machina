#include "tab-bar.h"

#include "imgui.h"

#include <functional>

namespace ui::components {

void tabBar(std::string_view title, std::function<void()> body)
{
  if (ImGui::BeginTabBar(title.data()))
  {
    body();

    ImGui::EndTabBar();
  }
}

void tabBarItem(std::string_view title, std::function<void()> body)
{
  if (ImGui::BeginTabItem(title.data()))
  {
    body();

    ImGui::EndTabItem();
  }
}

} // namespace ui::components
