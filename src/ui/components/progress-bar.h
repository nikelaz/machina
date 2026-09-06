#pragma once

/**
 * @file progress-bar.h
 * @brief Reusable progress bar component.
 */

#include <string>

namespace ui::components {

/**
 * @brief Renders a progress bar filling the available width.
 *
 * Uses a width of -FLT_MIN so it also spans the full current table cell
 * when called inside a table.
 *
 * @param fraction Progress value in the range [0.0, 1.0].
 * @param height Height of the bar in pixels.
 * @param overlay Overlay text rendered on top of the bar (empty for none).
 */
void progressBar(float fraction, float height = 22.0f, const std::string& overlay = "");

} // namespace ui::components
