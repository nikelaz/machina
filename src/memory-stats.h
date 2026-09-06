#pragma once

/**
 * @file memory-stats.h
 * @brief System memory usage sampling from /proc/meminfo.
 */

/**
 * @namespace memory_stats
 * @brief Reads memory usage information from /proc/meminfo.
 */
namespace memory_stats {

/**
 * @brief Snapshot of system memory usage.
 */
struct MemoryInfo
{
  double total_gb;     ///< Total physical memory in GB.
  double available_gb; ///< Memory available for new workloads (without swapping) in GB.
  double utilized;     ///< Fraction of memory in use, normalized to [0.0, 1.0].
};

/**
 * @brief Reads current memory usage from /proc/meminfo.
 *
 * Parses the MemTotal and MemAvailable entries.
 *
 * @return A MemoryInfo snapshot. Fields are zero-initialized if /proc/meminfo
 *         cannot be read or the expected entries are missing.
 */
MemoryInfo getMemoryInfo();

} // namespace memory_stats
