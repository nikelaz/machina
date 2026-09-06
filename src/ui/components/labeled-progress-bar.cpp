/**
 * @file labeled-progress-bar.cpp
 * @brief Implementation of the labeled progress bar component.
 */

#include "labeled-progress-bar.h"

#include "imgui.h"

namespace ui::components {

void labeledProgressBar(std::string_view label, float fraction, float bar_height,
                        const std::string& overlay)
{
  const float line_top = ImGui::GetCursorPosY();
  const float center_offset = (bar_height - ImGui::GetTextLineHeight()) * 0.5f;

  ImGui::SetCursorPosY(line_top + center_offset);
  ImGui::TextUnformatted(label.data(), label.data() + label.size());

  ImGui::SameLine(0.0f, 16.0f);
  ImGui::SetCursorPosY(line_top);
  ImGui::ProgressBar(fraction, ImVec2(-1, bar_height), overlay.c_str());
}

} // namespace ui::components
