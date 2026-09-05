#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <iostream>
#include <vector>

#include "SystemInfo.h"
#include "AppContext.h"
#include "ProcessReader.h"
#include "ProcessModel.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  // System info
  auto system_info_res = getSystemInfo();

  if (!system_info_res)
  {
    std::cerr << "Failed: " << system_info_res.error().message() << '\n';
    return 1;
  }

  SystemInformation system_info = *system_info_res;

  // Processes
  std::vector<process_reader::Process> processes = process_reader::getProcesses();
  ProcessModel process_model(processes);

  // QML Context
  AppContext::registerContext(engine, system_info, process_model);

  // Load QML
  engine.loadFromModule("SystemInfoQml", "Main");

  return app.exec();
}
