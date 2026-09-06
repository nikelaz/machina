#pragma once

/**
 * @file tab-bar.h
 * @brief Reusable ImGui tab bar and tab item components.
 */

#include <functional>
#include <string_view>

namespace ui::components {

/**
 * @brief Renders a tab bar wrapping the given tab items.
 *
 * Begins an ImGui tab bar, invokes @p body to draw the tab items, then
 * ends the tab bar. If the tab bar is not visible (e.g. clipped), @p body
 * is not called.
 *
 * @param title Tab bar title (also used as the ImGui ID).
 * @param body Callback drawing the tab items.
 */
void tabBar(std::string_view title, std::function<void()> body);

/**
 * @brief Renders a single tab item wrapping the given content.
 *
 * Begins an ImGui tab item, invokes @p body to draw its contents, then
 * ends the tab item. If the tab is not visible (not selected), @p body is
 * not called.
 *
 * @param title Tab label (also used as the ImGui ID).
 * @param body Callback drawing the tab's contents.
 */
void tabBarItem(std::string_view title, std::function<void()> body);

} // namespace ui::components
