#include <imgui.h>

class PlaybackManager;

struct ControlWindowState {
    bool is_playing;
};

void drawControlWindow(float x_size, float y_size, PlaybackManager& playback_manager);