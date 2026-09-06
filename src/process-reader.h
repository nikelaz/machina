#pragma once

/**
 * @file process-reader.h
 * @brief Reads the list of running processes from /proc.
 */

#include <vector>
#include <string>

/**
 * @namespace process_reader
 * @brief Reads the list of running processes from /proc.
 */
namespace process_reader {

/**
 * @brief A single running process.
 */
struct Process
{
  std::string pid;  ///< Process ID (as a string, as it appears in /proc).
  std::string name; ///< Process name (from /proc/&lt;pid&gt;/comm).
};

/**
 * @brief Enumerates all running processes.
 *
 * Scans /proc for numeric directories and reads each process name from
 * /proc/&lt;pid&gt;/comm.
 *
 * @return A list of running processes. Empty if /proc cannot be read.
 */
std::vector<Process> getProcesses();

} // namespace process_reader
