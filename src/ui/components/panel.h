#pragma once

#include "imgui.h"

#include <functional>
#include <string_view>

namespace ui::components {

void panel(std::string_view title, ImGuiWindowFlags flags, std::function<void()> body);

} // namespace ui::components
