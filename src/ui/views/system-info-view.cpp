/**
 * @file system-info-view.cpp
 * @brief Implementation of the system information view.
 */

#include "imgui.h"
#include <wayland-util.h>

#include "system-info-view.h"

#include "ui/components/labeled-progress-bar.h"

#include <format>

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

  components::labeledProgressBar(
    "CPU",
    state.cpu_utilization,
    22.0f,
    std::format("{:.0f}%", state.cpu_utilization * 100)
  );

  components::labeledProgressBar(
    "Memory",
    state.memory_info.utilized,
    22.0f,
    std::format("{:.0f}%", state.memory_info.utilized * 100)
  );

  ImGui::Text("Memory Total: %f GB", state.memory_info.total_gb);
  ImGui::Text("Memory Used: %f GB", state.memory_info.total_gb - state.memory_info.available_gb);
  ImGui::Text("Memory Available: %f GB", state.memory_info.available_gb);
}

} // namespace ui::views
