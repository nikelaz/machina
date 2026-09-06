#include "cpu-stats.h"

namespace cpu_stats {

ProcCpuStats readProcCpuStats()
{
  std::ifstream file("/proc/stat");

  std::string line;
  std::getline(file, line);

  std::istringstream stream(line);

  std::string cpu;
  ProcCpuStats stats{};

  stream >> cpu
         >> stats.user
         >> stats.nice
         >> stats.system
         >> stats.idle
         >> stats.iowait
         >> stats.irq
         >> stats.softirq
         >> stats.steal;

  return stats;
}

double getCpuUtilization(const ProcCpuStats& previous, const ProcCpuStats& current)
{
  uint64_t previous_idle = previous.idle + previous.iowait;

  uint64_t current_idle = current.idle + current.iowait;

  uint64_t previous_total =
    previous.user +
    previous.nice +
    previous.system +
    previous.idle +
    previous.iowait +
    previous.irq +
    previous.softirq +
    previous.steal;

  uint64_t current_total =
    current.user +
    current.nice +
    current.system +
    current.idle +
    current.iowait +
    current.irq +
    current.softirq +
    current.steal;

  uint64_t total_delta = current_total - previous_total;
  uint64_t idle_delta  = current_idle - previous_idle;

  if (total_delta == 0)
  {
    return 0.0;
  }

  return 1.0 - static_cast<double>(idle_delta) / total_delta;
}

double measureCpuUtilization()
{
  ProcCpuStats previous = readProcCpuStats();

  std::this_thread::sleep_for(std::chrono::milliseconds(250));

  ProcCpuStats current = readProcCpuStats();

  return getCpuUtilization(previous, current);
}

} // namespace cpu_stats
