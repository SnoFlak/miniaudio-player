#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

void init_ui(GLFWwindow* window);
void uninit_ui();
void draw_ui();
void render_draw_data();