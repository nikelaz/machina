#pragma once

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace process_reader {
  struct Process
  {
    std::string pid;
    std::string name;
  };

  std::vector<Process> getProcesses();
}

