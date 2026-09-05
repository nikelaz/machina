#include "SystemInfo.h"
#include <sys/utsname.h>

std::expected<SystemInformation, std::error_code>
getSystemInfo()
{
  SystemInformation system_info;
  utsname info;

  if (uname(&info) != 0)
  {
    return std::unexpected(std::error_code(errno, std::generic_category()));
  }

  system_info.os = info.sysname;
  system_info.hostname = info.nodename;
  system_info.kernel = info.release;
  system_info.arch = info.machine;

  return system_info;
}
