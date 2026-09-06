#pragma once

#include <functional>
#include <string_view>

namespace ui::components {

void tabBar(std::string_view title, std::function<void()> body);
void tabBarItem(std::string_view title, std::function<void()> body);

} // namespace ui::components
