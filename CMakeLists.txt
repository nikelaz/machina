cmake_minimum_required(VERSION 3.16)

project(SystemInfo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml QuickControls2)

qt_standard_project_setup()

qt_add_executable(SystemInfo
  ./src/Main.cpp
  ./src/SystemInfo.cpp
  ./src/AppContext.cpp
  ./src/ProcessReader.cpp
  ./src/ProcessModel.cpp
)

qt_add_qml_module(SystemInfo
  URI SystemInfoQml
  VERSION 1.0
  QML_FILES
    ./qml/Main.qml
    ./qml/ProcessList.qml
    ./qml/InfoView.qml
)

target_link_libraries(SystemInfo
  PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
)
