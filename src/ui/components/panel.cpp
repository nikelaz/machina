#include "panel.h"

namespace ui::components {

void panel(std::string_view title, ImGuiWindowFlags flags, std::function<void()> body)
{
  ImGui::Begin(title.data(), nullptr, flags);
  body();
  ImGui::End(); 
}

} // namespace ui::components

