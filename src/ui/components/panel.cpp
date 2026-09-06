/**
 * @file panel.cpp
 * @brief Implementation of the panel component.
 */

#include "panel.h"

namespace ui::components {

/**
 * @brief Renders a panel window wrapping the given body content.
 */
void panel(std::string_view title, ImGuiWindowFlags flags, std::function<void()> body)
{
  ImGui::Begin(title.data(), nullptr, flags);
  body();
  ImGui::End(); 
}

} // namespace ui::components

