#include <imgui.h>
#include <iostream>
#include "playback_manager.h"

// struct ControlWindowState {
//     bool is_playing = false;
// } CWState;

void drawControlWindow(float x_size, float y_size, PlaybackManager& playback_manager) {
    ImVec2 controlbar_size = ImVec2(0.0f, y_size * 0.15 < 45.0f ? 45.0f : y_size * 0.15 > 65.0f ? 65.0f : y_size * 0.15);
    ImGui::BeginChild("ControlBar", controlbar_size, ImGuiChildFlags_Borders);
    if(ImGui::Button(playback_manager.IsPlaying() == true ? "Pause" : "Play", ImVec2(40.0f, 40.0f))) {
        if(playback_manager.IsPlaying() == true){
            playback_manager.Stop();
        } else {
            playback_manager.Play();
        }
    }
    ImGui::SameLine();
    ImGui::BeginChild("TitleSeek", ImVec2(0.0f, 0.0f));
    ImGui::Text(playback_manager.file_name);
    //some seekbar thing with pcms

    ImGui::EndChild();
    ImGui::EndChild();
}