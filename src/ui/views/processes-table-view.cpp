#include "processes-table-view.h"
#include "imgui.h"

#include <memory>
#include <atomic>

namespace ui::views {

void processesTableView(const AppState& state)
{
  const ImGuiTableFlags table_flags = ImGuiTableFlags_Borders |
                                      ImGuiTableFlags_RowBg |
                                      ImGuiTableFlags_ScrollY |
                                      ImGuiTableFlags_Resizable;

  if (ImGui::BeginTable("ProcessList", 2, table_flags))
  {
    ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 80.0f);
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupScrollFreeze(0, 1);
    ImGui::TableHeadersRow();

    ImGuiListClipper clipper;
    clipper.Begin(static_cast<int>(state.processes.size()));
    while (clipper.Step())
    {
      for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
      {
        const auto& proc = state.processes[static_cast<size_t>(row)];
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(proc.pid.c_str());
        ImGui::TableNextColumn();
        ImGui::TextUnformatted(proc.name.c_str());
      }
    }

    ImGui::EndTable();
  }
}

} // namespace ui::views
