#pragma once

/**
 * @file panel.h
 * @brief Reusable ImGui panel (full-window container) component.
 */

#include "imgui.h"

#include <functional>
#include <string_view>

namespace ui::components {

/**
 * @brief Renders a panel window wrapping the given body content.
 *
 * Begins an ImGui window with the given title and flags, invokes @p body
 * to draw the contents, then ends the window.
 *
 * @param title Panel title (also used as the ImGui window ID).
 * @param flags ImGui window flags for the panel.
 * @param body Callback drawing the panel's contents.
 */
void panel(std::string_view title, ImGuiWindowFlags flags, std::function<void()> body);

} // namespace ui::components
