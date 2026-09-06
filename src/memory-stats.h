#pragma once

namespace memory_stats {

struct MemoryInfo
{
  double total_gb;
  double available_gb;
  double utilized;
};

MemoryInfo getMemoryInfo();

} // namespace memory_stats
