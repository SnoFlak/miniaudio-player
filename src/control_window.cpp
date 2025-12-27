#include <imgui.h>
#include <iostream>
#include "playback_manager.h"

float timeline_value = 0.0f;
float old_timeline_value = 0.0f;
bool seeking = false;

void GetPlayTime(PlaybackManager& playback_manager);

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

    //if we're playing, we should be updating the timeline_value with GrabTime()
    //HOWEVER, if IsItemActive(), we want to stop this.
    //when IsItemEdited, it will update timeline_value, then, when IsItemActive is false, we should send off the updated timeline_value to playback_manager, and have
    //the playback_manager seek to the new position.

    ImGui::PushID(1337); // needed to have empty label for slider, so we use ID's in place of label
    ImGui::SliderFloat("", &timeline_value, 0.0f, playback_manager.cur_sound_length, "");
    if(ImGui::IsItemActive()){
        seeking = true;
    } else {

        if((old_timeline_value != timeline_value) && (seeking == true)) {
            std::cout << "[ControlWindow] old_timeline_value != timeline_value, attempting seek..." << std::endl;
            seeking = false;
            playback_manager.SeekTo(timeline_value, playback_manager.IsPlaying());
        }

        if((playback_manager.IsPlaying() == true) && (seeking == false)){
            timeline_value = playback_manager.GrabTime();
            old_timeline_value = timeline_value;
        }
    }

    // save slider float value to local variable, so we can grab it when IsItemActive and IsItemEdited are true, then we can use seek to time based off that value, and update the sound
    
    //IsItemActive()
    //IsItemEdited()
    ImGui::PopID();
    ImGui::EndChild();

    ImGui::EndChild();
}

// void GetPlayTime(PlaybackManager& playback_manager) {
//     ma_result res = ma_sound_get_cursor_in_seconds(playback_manager.GrabSound(), playback_manager.GrabTime());
//     if (res != MA_SUCCESS) {
//         std::cout << "[ControlWindow] ERROR: failed to GetPlayTime" << std::endl;
//         return;
//     }
// }