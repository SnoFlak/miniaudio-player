#include <imgui.h>
#include <filesystem>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "playback_manager.h"

enum FileType {
    DIRECTORY,
    AUDIOFILE,
    UNKNOWN,    //used to define unsupported files, will probably just ignore these in the future; can also be used to have unsupported files still listed?
    EMPTY       //used to define an empty Music folder, so we're not constantly searching through for discovered_files
};

struct CachedFile {
    std::filesystem::path file_path;
    FileType type = UNKNOWN;
    std::string file_name;
};

struct DirectoryWindowState {
    std::filesystem::path current_path = "";
    std::vector<CachedFile> discovered_files;
} DWState;

void searchDirectory();
void buildNodesFromCachedFiles(PlaybackManager& playback_manager);

void drawDirectoryWindow(float x_size, float y_size, PlaybackManager& playback_manager) {
    ImVec2 directory_size = ImVec2(x_size / 3 < 100.0f ? 100.0f : x_size / 3, y_size * 0.8 < 240.0f ? 240.0f : y_size * 0.8);
    ImGui::BeginChild("Sidebar", directory_size, ImGuiChildFlags_Borders);
    if(ImGui::TreeNode("Music")) {
        if(DWState.discovered_files.size() == 0) {
            searchDirectory();
            buildNodesFromCachedFiles(playback_manager);
        } else if(DWState.discovered_files[0].type == EMPTY){
            ImGui::Text("No Files/Directories Found...");
        } else {
            buildNodesFromCachedFiles(playback_manager);
        }  
        ImGui::TreePop();
    }
    ImGui::EndChild();
}

void searchDirectory() {
    
    const char* home_dir_c_str = nullptr;

    #ifdef _WIN32
        home_dir_c_str = std::getenv("USERPROFILE");
    #else
        home_dir_c_str = std::getenv("HOME");
    #endif

    std::filesystem::path homeDirectory(home_dir_c_str);
    DWState.current_path = homeDirectory / "Music";

    if (home_dir_c_str == nullptr) {
        std::cerr << "Error: Could not determine home directory." << std::endl;
        return;
    }

    try {
        std::cout << DWState.current_path << std::endl;
        int DIcount = 0;
        for (const auto& entry : std::filesystem::directory_iterator(DWState.current_path)) {
            if (std::filesystem::is_directory(entry.status())) {
                std::cout << " (Directory) " << std::endl;
                DWState.discovered_files.push_back({std::filesystem::absolute(entry.path()), DIRECTORY, entry.path().filename().string()});
            } else if (std::filesystem::is_regular_file(entry.status())) {
                std::cout << " (file: " << entry.path().filename() << ")" << std::endl;
                if (entry.path().filename().string().find(".mp3") != std::string::npos) {
                    DWState.discovered_files.push_back({std::filesystem::absolute(entry.path()), AUDIOFILE, entry.path().filename().string()});
                }
            }
            DIcount += 1;
        }

        if(DIcount == 0) { // directory_iterator couldn't find files in path, so populate a CachedFile with type EMPTY to handle checks in drawDirectoryWindow
            DWState.discovered_files[0] = {std::filesystem::path(""), EMPTY};
        }

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error iterating directory: " << e.what() << std::endl;
    }
}

void buildNodesFromCachedFiles(PlaybackManager& playback_manager) {
    for(int i = 0; i < DWState.discovered_files.size(); i++) {
        switch(DWState.discovered_files[i].type) {
            case DIRECTORY:
                break;
            case AUDIOFILE:
                // if(ImGui::TreeNode(DWState.discovered_files[i].file_name)) {
                //     ImGui::TreePop();
                // }
                ImGui::PushID(i);
                if(ImGui::Button(DWState.discovered_files[i].file_name.c_str())) {
                    //load music file here
                    std::cout << "[UI] selected music file: " << DWState.discovered_files[i].file_name << std::endl;
                    std::cout << "[UI] passing filepath to PlaybackManager: " << DWState.discovered_files[i].file_path.c_str() << std::endl;
                    playback_manager.Play(DWState.discovered_files[i].file_path.c_str(), DWState.discovered_files[i].file_name.c_str());
                }
                ImGui::PopID();
                break;
            case UNKNOWN:
            case EMPTY:
                break;
            default:
                break;

        }
    }
}
