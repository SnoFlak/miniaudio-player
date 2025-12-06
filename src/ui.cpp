#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "control_window.h"
#include "directory_window.h"
#include "visualizer_window.h"


void init_ui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void uninit_ui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void draw_ui() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 sidebar_size = ImVec2(viewport->Size.x / 3 < 100.0f ? 100.0f : viewport->Size.x / 3, viewport->Size.y * 0.8 < 240.0f ? 240.0f : viewport->Size.y * 0.8);
    ImVec2 visualizer_size = ImVec2(0.0f, viewport->Size.y * 0.8 < 240.0f ? 240.0f : viewport->Size.y * 0.8);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::Begin("Hello ImGui", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    draw_directory_window(viewport->Size.x, viewport->Size.y);
    ImGui::SameLine();
    draw_visualizer_window(viewport->Size.x, viewport->Size.y);

    draw_control_window(viewport->Size.x, viewport->Size.y);
    // ImGui::ShowDemoWindow();
    ImGui::End();

    ImGui::Render();
}

void render_draw_data() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}