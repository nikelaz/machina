#pragma once

#include "process-reader.h"
#include "system-info.h"

#include <vector>

struct AppState {
  std::vector<process_reader::Process> processes;
  SystemInformation system_info;
};
