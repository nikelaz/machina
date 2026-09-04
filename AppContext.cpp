#include "AppContext.h"

#include <QQmlContext>

void AppContext::registerContext(
  QQmlApplicationEngine& engine,
  SystemInformation& system_info
)
{
  engine.rootContext()->setContextProperty(
    "os",
    QString::fromStdString(system_info.os)
  );

  engine.rootContext()->setContextProperty(
    "hostname",
    QString::fromStdString(system_info.hostname)
  );

  engine.rootContext()->setContextProperty(
    "kernel",
    QString::fromStdString(system_info.kernel)
  );

  engine.rootContext()->setContextProperty(
    "arch",
    QString::fromStdString(system_info.arch)
  );
}
