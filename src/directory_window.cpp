#include <imgui.h>
#include <filesystem>

// struct VisualizerWindowState {
//     bool is_playing = false;
// };

void draw_directory_window(float x_size, float y_size) {
    ImVec2 directory_size = ImVec2(x_size / 3 < 100.0f ? 100.0f : x_size / 3, y_size * 0.8 < 240.0f ? 240.0f : y_size * 0.8);
    ImGui::BeginChild("Sidebar", directory_size, ImGuiChildFlags_Borders);
    ImGui::Text("test text");
    ImGui::EndChild();
}
