#pragma once

#include <QQmlApplicationEngine>
#include "SystemInfo.h"

namespace AppContext {
  void registerContext(QQmlApplicationEngine& engine, SystemInformation& system_info);
}
