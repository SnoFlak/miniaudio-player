#include <imgui.h>
#include <iostream>

struct ControlWindowState {
    bool is_playing = false;
} CWState;

void drawControlWindow(float x_size, float y_size) {
    ImVec2 controlbar_size = ImVec2(0.0f, y_size * 0.15 < 45.0f ? 45.0f : y_size * 0.15 > 65.0f ? 65.0f : y_size * 0.15);
    ImGui::BeginChild("ControlBar", controlbar_size, ImGuiChildFlags_Borders);
    if(ImGui::Button(CWState.is_playing == true ? "Pause" : "Play", ImVec2(40.0f, 40.0f))) {
        CWState.is_playing = !CWState.is_playing;
    }
    ImGui::SameLine();
    ImGui::EndChild();
}