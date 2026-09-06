#include "memory-stats.h"

#include <fstream>
#include <string>

/**
 * @file memory-stats.cpp
 * @brief Implementation of memory usage sampling from /proc/meminfo.
 */

namespace memory_stats {

/**
 * @brief Reads current memory usage from /proc/meminfo.
 */
MemoryInfo getMemoryInfo()
{
  std::ifstream file("/proc/meminfo");

  long long total_kb = 0;
  long long available_kb = 0;

  std::string name;
  long long value;
  std::string unit;

  while (file >> name >> value >> unit)
  {
    if (name == "MemTotal:")
      total_kb = value;
    else if (name == "MemAvailable:")
      available_kb = value;
  }

  constexpr double KB_TO_GB = 1.0 / (1024.0 * 1024.0);

  double total_gb = total_kb * KB_TO_GB;
  double available_gb = available_kb * KB_TO_GB;

  double utilized =
    static_cast<double>(total_kb - available_kb) / total_kb;

  return {
    total_gb,
    available_gb,
    utilized
  };
}

} // namespace memory_stats
