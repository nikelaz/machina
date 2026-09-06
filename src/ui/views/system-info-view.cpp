/**
 * @file system-info-view.cpp
 * @brief Implementation of the system information view.
 */

#include "imgui.h"
#include <wayland-util.h>

#include "system-info-view.h"

#include "memory-stats.h"
#include "system-info.h"

#include "ui/components/progress-bar.h"

#include <format>
#include <string>
#include <string_view>

namespace ui::views {

/// Width of the fixed label column shared by all info tables.
constexpr float kLabelColumnWidth = 120.0f;

/// Height of the progress bars in the info tables.
constexpr float kBarHeight = 22.0f;

/**
 * @brief Begins a two-column info table (fixed label column, stretched value column).
 *
 * @param id ImGui ID of the table (must be unique among sibling tables).
 */
void beginInfoTable(const char* id)
{
  ImGui::BeginTable(id, 2, ImGuiTableFlags_None);
  ImGui::TableSetupColumn("label", ImGuiTableColumnFlags_WidthFixed, kLabelColumnWidth);
  ImGui::TableSetupColumn("value", ImGuiTableColumnFlags_WidthStretch);
}

/**
 * @brief Ends the current info table.
 */
void endInfoTable()
{
  ImGui::EndTable();
}

/**
 * @brief Adds a label/value text row to the current info table.
 *
 * @param label Row label (drawn in the label column).
 * @param value Row value (drawn in the value column).
 */
void infoRow(std::string_view label, const std::string& value)
{
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  ImGui::TextUnformatted(label.data(), label.data() + label.size());
  ImGui::TableNextColumn();
  ImGui::TextUnformatted(value.c_str());
}

/**
 * @brief Adds a label/progress-bar row to the current info table.
 *
 * @param label Row label (drawn in the label column).
 * @param fraction Progress value in the range [0.0, 1.0].
 * @param overlay Overlay text rendered on top of the bar.
 */
void barRow(std::string_view label, float fraction, const std::string& overlay)
{
  ImGui::TableNextRow();
  ImGui::TableNextColumn();
  ImGui::TextUnformatted(label.data(), label.data() + label.size());
  ImGui::TableNextColumn();
  components::progressBar(fraction, kBarHeight, overlay);
}

/**
 * @brief Renders system information and CPU/memory stats in aligned tables.
 */
void systemInfoView(const AppState& state)
{
  ImGui::SeparatorText("System");
  beginInfoTable("system");
  infoRow("OS", state.system_info.os);
  infoRow("Hostname", state.system_info.hostname);
  infoRow("Kernel", state.system_info.kernel);
  infoRow("Arch", state.system_info.arch);
  endInfoTable();

  ImGui::SeparatorText("CPU & Memory");
  beginInfoTable("cpu-mem");
  barRow("CPU", state.cpu_utilization,
         std::format("{:.0f}%", state.cpu_utilization * 100));
  barRow("Memory", state.memory_info.utilized,
         std::format("{:.0f}%", state.memory_info.utilized * 100));
  infoRow("Total", std::format("{:.2f} GB", state.memory_info.total_gb));
  infoRow("Used",
          std::format("{:.2f} GB", state.memory_info.total_gb - state.memory_info.available_gb));
  infoRow("Available", std::format("{:.2f} GB", state.memory_info.available_gb));
  endInfoTable();
}

} // namespace ui::views
