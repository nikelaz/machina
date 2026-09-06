#pragma once

#include <vector>
#include <string>

/**
 * @namespace process_reader
 * @brief Reads the list of running processes from /proc.
 */
namespace process_reader {
  struct Process
  {
    std::string pid;
    std::string name;
  };

  std::vector<Process> getProcesses();
}

