#pragma once

/**
 * @file app-state.h
 * @brief Immutable snapshot of all data shared between the background
 *        collector thread and the UI thread.
 */

#include "process-reader.h"
#include "system-info.h"

#include <vector>

/**
 * @brief Aggregated snapshot of system data used for rendering a frame.
 *
 * Instances are built by the background worker thread and published to the
 * UI thread via an atomic shared_ptr, so they are treated as immutable.
 */
struct AppState {
  std::vector<process_reader::Process> processes; ///< Currently running processes.
  SystemInformation system_info;                  ///< Static system information (OS, kernel, etc.).
};
