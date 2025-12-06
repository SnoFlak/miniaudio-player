#include <imgui.h>

// struct VisualizerWindowState {
//     bool is_playing = false;
// };

void draw_visualizer_window(float x_size, float y_size) {
    ImVec2 visualizer_size = ImVec2(0.0f, y_size * 0.8 < 240.0f ? 240.0f : y_size * 0.8);
    ImGui::BeginChild("Visualizer", visualizer_size, ImGuiChildFlags_Borders);
    ImGui::Text("test text");
    ImGui::EndChild();
}