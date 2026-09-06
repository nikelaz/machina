#pragma once

/**
 * @file main-view.h
 * @brief Root view containing the application's tabbed layout.
 */

#include "app-state.h"

#include <memory>

namespace ui::views {

/**
 * @brief Renders the root window with the main tab bar.
 *
 * Hosts the "Info" (system information) and "Processes" tabs as children.
 *
 * @param state The application state snapshot to render from.
 */
void mainView(const AppState& state);

} // namespace ui::views
