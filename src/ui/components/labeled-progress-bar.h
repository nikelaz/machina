#pragma once

/**
 * @file labeled-progress-bar.h
 * @brief Reusable component for a label aligned with a progress bar.
 */

#include <string>
#include <string_view>

namespace ui::components {

/**
 * @brief Renders a text label vertically centered next to a progress bar.
 *
 * The label is centered against the bar's height, and the bar fills the
 * remaining available width of the current line.
 *
 * @param label Text label drawn to the left of the bar.
 * @param fraction Progress value in the range [0.0, 1.0].
 * @param bar_height Height of the progress bar in pixels.
 * @param overlay Overlay text rendered on top of the bar (empty for none).
 */
void labeledProgressBar(std::string_view label, float fraction, float bar_height = 22.0f,
                        const std::string& overlay = "");

} // namespace ui::components
