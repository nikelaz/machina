#include "main-view.h"

#include "imgui.h"

#include "ui/components/panel.h"
#include "ui/components/tab-bar.h"
#include "ui/views/system-info-view.h"
#include "ui/views/processes-table-view.h"

using namespace ui::components;

namespace ui::views {

void mainView(const AppState& state)
{
  ImGuiWindowFlags canvas_flags = ImGuiWindowFlags_NoDecoration |
                                  ImGuiWindowFlags_NoBringToFrontOnFocus |
                                  ImGuiWindowFlags_NoSavedSettings;

  panel("Main", canvas_flags, [&]() {
    tabBar("MainTabs", [&]() {
      tabBarItem("Info", [&state]() {
        systemInfoView(state);
      });

      tabBarItem("Processes", [&state]() {
        processesTableView(state);
      });
    });
  });
}

} // namespace ui::views
