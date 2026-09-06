/**
 * @file system-info-view.cpp
 * @brief Implementation of the system information view.
 */

#include "imgui.h"

#include "system-info-view.h"

#include <memory>
#include <atomic>

namespace ui::views {

/**
 * @brief Renders OS, hostname, kernel and architecture details as text.
 */
void systemInfoView(const AppState& state)
{
  ImGui::Text("OS:       %s", state.system_info.os.c_str());
  ImGui::Text("Hostname: %s", state.system_info.hostname.c_str());
  ImGui::Text("Kernel:   %s", state.system_info.kernel.c_str());
  ImGui::Text("Arch:     %s", state.system_info.arch.c_str());
}

} // namespace ui::views
