#include "ProcessReader.h"

namespace fs = std::filesystem;

namespace process_reader {
  std::vector<Process> getProcesses()
  {
    auto dir_iterator = fs::directory_iterator("/proc");
    std::vector<Process> output;

    for (const auto& entry : dir_iterator)
    {
      if (!entry.is_directory())
      {
        continue;
      }

      std::string pid_dirname = entry.path().filename().string();
      bool is_process_dir = std::all_of(pid_dirname.begin(), pid_dirname.end(), ::isdigit);

      if (pid_dirname.empty() || !is_process_dir)
      {
        continue;
      }

      std::ifstream comm_file("/proc/" + pid_dirname + "/comm");
      std::string process_name;
      std::getline(comm_file, process_name);

      output.emplace_back(pid_dirname, process_name);
    }

    return output;
  }
}
