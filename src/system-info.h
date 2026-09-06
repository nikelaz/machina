#pragma once

/**
 * @file system-info.h
 * @brief Static system information (OS, hostname, kernel, architecture).
 */

#include <string>
#include <expected>
#include <system_error>

/**
 * @brief Basic identification details of the running system.
 */
struct SystemInformation
{
  std::string os;       ///< Operating system name (e.g. "Linux").
  std::string hostname; ///< Network node name / hostname.
  std::string kernel;   ///< Kernel release string.
  std::string arch;     ///< Machine architecture (e.g. "x86_64").
};

/**
 * @brief Retrieves static system information via uname(2).
 *
 * @return The collected SystemInformation, or an std::error_code if the
 *         uname call fails.
 */
std::expected<SystemInformation, std::error_code> getSystemInfo();
