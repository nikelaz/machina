#pragma once

/**
 * @file processes-table-view.h
 * @brief View displaying the running process list in a table.
 */

#include "app-state.h"

#include <memory>
#include <atomic>

namespace ui::views {

/**
 * @brief Renders the running process list as a scrollable PID/Name table.
 *
 * Uses ImGuiListClipper so only visible rows are rendered.
 *
 * @param state The application state snapshot to render from.
 */
void processesTableView(const AppState& state);

} // namespace ui::views
