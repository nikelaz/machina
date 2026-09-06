cmake_minimum_required(VERSION 3.16)
project(Machina VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile_commands.json for clangd / language servers
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ImGui

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

add_library(imgui STATIC
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
  ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
  ${IMGUI_DIR}
  ${IMGUI_DIR}/backends
)

target_compile_definitions(imgui PUBLIC IMGUI_DEFINE_MATH_OPERATORS)

# GLFW

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# Application 

add_executable(machina
  ./src/main.cpp
  ./src/application.cpp
  ./src/system-info.cpp
  ./src/process-reader.cpp
  ./src/cpu-stats.cpp
  ./src/memory-stats.cpp
  ./src/ui/ui-system.cpp
  ./src/ui/views/main-view.cpp
  ./src/ui/views/system-info-view.cpp
  ./src/ui/views/processes-table-view.cpp
  ./src/ui/components/panel.cpp
  ./src/ui/components/tab-bar.cpp
  ./src/ui/components/labeled-progress-bar.cpp
  ./src/ui/components/progress-bar.cpp
)

target_include_directories(machina PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# fontconfig (for loading the system font)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FONTCONFIG REQUIRED IMPORTED_TARGET fontconfig)

target_link_libraries(machina
  PRIVATE
    imgui
    PkgConfig::FONTCONFIG
)

# Docs
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_custom_target(docs
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/docs
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )
endif()
