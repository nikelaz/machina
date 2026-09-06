/**
 * @file system-info-view.cpp
 * @brief Implementation of the system information view.
 */

#include "imgui.h"

#include "system-info-view.h"

namespace ui::views {

/**
 * @brief Renders OS, hostname, kernel and architecture details as text.
 */
void systemInfoView(const AppState& state)
{
  ImGui::SeparatorText("System");
  ImGui::Text("OS:        %s", state.system_info.os.c_str());
  ImGui::Text("Hostname:  %s", state.system_info.hostname.c_str());
  ImGui::Text("Kernel:    %s", state.system_info.kernel.c_str());
  ImGui::Text("Arch:      %s", state.system_info.arch.c_str());

  ImGui::SeparatorText("CPU & Memory");
  ImGui::Text("CPU %.0f%%", state.cpu_utilization * 100);
  ImGui::SameLine(0.0f, 16.0f); 
  ImGui::ProgressBar(
    state.cpu_utilization,
    ImVec2(-1, 13),
    ""
  );
}

} // namespace ui::views
