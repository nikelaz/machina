#include "application.h"

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "process-reader.h"
#include "system-info.h"

#include <chrono>
#include <cstdio>
#include <vector>

static GLFWwindow* createWindow()
{
  // TODO: better error handling
  if (!glfwInit())
  {
    std::fprintf(stderr, "glfw init failed\n");
    return nullptr;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  const int window_width = 500;
  const int window_height = 500;
  const char* window_title = "System Information";

  GLFWwindow* window = glfwCreateWindow(
    window_width,
    window_height,
    "System Information",
    nullptr,
    nullptr
  );

  // TODO: better error handling
  if (!window)
  {
    std::fprintf(stderr, "glfwCreateWindow failed\n");
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  return window;
}

static void setupImGui(GLFWwindow* window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

static void newFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Application::run()
{
  GLFWwindow* window = createWindow();
  setupImGui(window);

  // Process list cache — refreshed at most once per second.
  // TODO: move this fetch to the std::thread polling worker.
  std::vector<process_reader::Process> processes;
  std::chrono::steady_clock::time_point last_fetch{};
  constexpr auto fetch_interval = std::chrono::seconds(1);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    auto now = std::chrono::steady_clock::now();
    if (now - last_fetch > fetch_interval)
    {
      processes = process_reader::getProcesses();
      last_fetch = now;
    }
    
    newFrame();

    // Prepare Viewport
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGuiWindowFlags canvas_flags = ImGuiWindowFlags_NoDecoration | 
                                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                                    ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("Main", nullptr, canvas_flags);

    if (ImGui::BeginTabBar("MainTabs"))
    {
      if (ImGui::BeginTabItem("Info"))
      {
        if (auto info = getSystemInfo())
        {
          ImGui::Text("OS:       %s", info->os.c_str());
          ImGui::Text("Hostname: %s", info->hostname.c_str());
          ImGui::Text("Kernel:   %s", info->kernel.c_str());
          ImGui::Text("Arch:     %s", info->arch.c_str());
        }
        else
        {
          ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "Failed: %s",
                             info.error().message().c_str());
        }
        ImGui::EndTabItem();
      }

      if (ImGui::BeginTabItem("Processes"))
      {
        if (ImGui::BeginTable(
              "ProcessList", 2,
              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY | ImGuiTableFlags_Resizable))
        {
          ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 80.0f);
          ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
          ImGui::TableSetupScrollFreeze(0, 1); // keep header visible while scrolling
          ImGui::TableHeadersRow();

          // Only the visible rows are submitted — handles hundreds of processes.
          ImGuiListClipper clipper;
          clipper.Begin(static_cast<int>(processes.size()));
          while (clipper.Step())
          {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
            {
              const auto& proc = processes[static_cast<size_t>(row)];
              ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::TextUnformatted(proc.pid.c_str());
              ImGui::TableNextColumn();
              ImGui::TextUnformatted(proc.name.c_str());
            }
          }

          ImGui::EndTable();
        }
        ImGui::EndTabItem();
      }

      ImGui::EndTabBar();
    }

    ImGui::End();

    ImGui::Render();

    // prepare backbuffer
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // render backbuffer
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
}

