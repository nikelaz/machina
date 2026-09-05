#pragma once

#include <QQmlApplicationEngine>
#include "SystemInfo.h"
#include "ProcessModel.h"

namespace AppContext {
  void registerContext(
    QQmlApplicationEngine& engine,
    SystemInformation& system_info,
    ProcessModel& process_model
  );
}
