#pragma once

#include <string>
#include <expected>
#include <system_error>

struct SystemInformation
{
  std::string os;
  std::string hostname;
  std::string kernel;
  std::string arch;
};

std::expected<SystemInformation, std::error_code> getSystemInfo();
