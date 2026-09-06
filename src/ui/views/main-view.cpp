/**
 * @file main-view.cpp
 * @brief Implementation of the root tabbed view.
 */

#include "main-view.h"

#include "imgui.h"

#include "ui/components/panel.h"
#include "ui/components/tab-bar.h"
#include "ui/views/system-info-view.h"
#include "ui/views/processes-table-view.h"

using namespace ui::components;

namespace ui::views {

/**
 * @brief Renders the root window with the main tab bar.
 */
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
