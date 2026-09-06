#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

/**
 * @namespace cpu_stats
 * @brief CPU utilization sampling and calculation.
 */
namespace cpu_stats {

struct ProcCpuStats {
  uint64_t user;
  uint64_t nice;
  uint64_t system;
  uint64_t idle;
  uint64_t iowait;
  uint64_t irq;
  uint64_t softirq;
  uint64_t steal;
};

/**
 * Reads aggregate CPU statistics for all cores from /proc/stat.
 *
 * Only the first (aggregate "cpu") line is parsed; per-core
 * lines are ignored.
 *
 * @return A ProcCpuStats struct with the time split. Fields are
 *         zero-initialized if /proc/stat cannot be read.
 */
ProcCpuStats readProcCpuStats();

/**
 * Calculates system-wide CPU utilization between two samples.
 *
 * @param previous CPU statistics from the previous sample.
 * @param current CPU statistics from the current sample.
 * @return CPU utilization as a normalized value in the range [0.0, 1.0].
 */
double getCpuUtilization(const ProcCpuStats& previous, const ProcCpuStats& current);

/**
 * Measures CPU utilization over a 250 ms sampling interval.
 *
 * Warning: This function blocks for approximately 250 ms.
 * Do not call this function from the main thread.
 *
 * @return CPU utilization as a normalized value in the range [0.0, 1.0].
 */
double measureCpuUtilization();

} // namespace cpu_stats
