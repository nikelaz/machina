/**
 * @file progress-bar.cpp
 * @brief Implementation of the progress bar component.
 */

#include "progress-bar.h"

#include "imgui.h"

#include <cfloat>

namespace ui::components {

void progressBar(float fraction, float height, const std::string& overlay)
{
  // -FLT_MIN: fill the remaining width of the current region (or table cell).
  ImGui::ProgressBar(fraction, ImVec2(-FLT_MIN, height), overlay.c_str());
}

} // namespace ui::components
