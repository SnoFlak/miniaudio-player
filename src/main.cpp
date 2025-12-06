// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ui.h"

#include <iostream>

void processInput(GLFWwindow *window);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 450, "miniaudio-player", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    int min_width = 500;
    int min_height = 300;
    int max_width = 800;
    int max_height = 450;

    glfwSetWindowSizeLimits(
        window, 
        min_width, 
        min_height, 
        max_width, 
        max_height
    );

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 330");

    init_ui(window);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.00f);
    // const ImGuiViewport* viewport = ImGui::GetMainViewport();
    // ImGuiStyle& style = ImGui::GetStyle();

    while(!glfwWindowShouldClose(window)) {
        // ImVec2 sidebar_size = ImVec2(viewport->Size.x / 3 < 100.0f ? 100.0f : viewport->Size.x / 3, viewport->Size.y * 0.8 < 240.0f ? 240.0f : viewport->Size.y * 0.8);
        // ImVec2 visualizer_size = ImVec2(0.0f, viewport->Size.y * 0.8 < 240.0f ? 240.0f : viewport->Size.y * 0.8);
        // ImVec2 controlbar_size = ImVec2(0.0f, viewport->Size.y * 0.15 < 45.0f ? 45.0f : viewport->Size.y * 0.15 > 65.0f ? 65.0f : viewport->Size.y * 0.15);
        glfwPollEvents();

        draw_ui();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        render_draw_data();

        glfwSwapBuffers(window);
    }

    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
    uninit_ui();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
