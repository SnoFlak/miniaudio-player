#include <imgui.h>
#include <filesystem>
#include <cstdlib>
#include <vector>

class PlaybackManager;

void drawDirectoryWindow(float x_size, float y_size, PlaybackManager& playback_manager);
void searchDirectory();
void buildNodesFromCachedFiles(PlaybackManager& playback_manager);