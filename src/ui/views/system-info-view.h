#pragma once

/**
 * @file system-info-view.h
 * @brief View displaying static system information.
 */

#include "app-state.h"

#include <memory>
#include <atomic>

namespace ui::views {

/**
 * @brief Renders OS, hostname, kernel and architecture details as text.
 *
 * @param state The application state snapshot to render from.
 */
void systemInfoView(const AppState& state);

} // namespace ui::views
