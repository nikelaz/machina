#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <iostream>

#include "SystemInfo.h"
#include "AppContext.h"

int main(int argc, char *argv[])
{
  auto system_info_res = getSystemInfo();

  if (!system_info_res)
  {
    std::cerr << "Failed: " << system_info_res.error().message() << '\n';
    return 1;
  }

  SystemInformation system_info = *system_info_res;

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  AppContext::registerContext(engine, system_info);

  engine.loadFromModule("SystemInfoQml", "Main");
  return app.exec();
}
