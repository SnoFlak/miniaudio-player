#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "playback_manager.h"
#include <iostream>

PlaybackManager::PlaybackManager() {
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine." << std::endl;
        return;
    }

    sound = {};
}

PlaybackManager::~PlaybackManager() {
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
}

void PlaybackManager::Play() {
    if(sound.pDataSource != nullptr){
        ma_sound_start(&sound);
    }
}

void PlaybackManager::Play(const char* file) {
    if (sound.pDataSource != nullptr) {
        ma_sound_uninit(&sound);
    }
    result = ma_sound_init_from_file(&engine, file, 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        std::cout << "[PlaybackManager] ERROR: failed to init sound from file: " << file << std::endl;
        return;
    }
    std::cout << "[PlaybackManager] playing music file: " << file << std::endl;
    ma_sound_start(&sound);   
}

void PlaybackManager::Stop() {
    ma_sound_stop(&sound);
}
