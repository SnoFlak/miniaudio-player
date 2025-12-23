#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "playback_manager.h"
#include <iostream>

void my_end_callback(void* pUserData, ma_sound* pSound);

PlaybackManager::PlaybackManager() {
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cout << "Failed to initialize audio engine." << std::endl;
        return;
    }

    sound = {};
    sound_config = ma_sound_config_init_2(&engine);
    // init config params
    sound_config.endCallback = my_end_callback;

    //utilize ma_sound_init_ex(&sound_config, &sound) in place of ma_sound_init_from_file
    //when changing audio files, replace soundConfig.pfilePath, then call ma_sound_init_ex
    file_name = "";
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

void PlaybackManager::Play(const char* file, const char* f_name) {
    if (sound.pDataSource != nullptr) {
        ma_sound_uninit(&sound);
    }
    sound_config.pFilePath = file;
    result = ma_sound_init_ex(&engine, &sound_config, &sound);
    // result = ma_sound_init_from_file(&engine, file, 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        std::cout << "[PlaybackManager] ERROR: failed to init sound from file: " << file << std::endl;
        return;
    }
    file_name = f_name;

    std::cout << "[PlaybackManager] playing music file: " << file << std::endl;
    ma_sound_start(&sound);   
}

void PlaybackManager::Stop() {
    ma_sound_stop(&sound);
}

bool PlaybackManager::IsPlaying() {
    return ma_sound_is_playing(&sound);
}

void my_end_callback(void* pUserData, ma_sound* pSound) {
    std::cout << "[PlaybackManager] my_end_callback: song ended" << std::endl;
    ma_uint64 len;
    std::cout << "[PlaybackManager] length in pcm frames: " << ma_sound_get_length_in_pcm_frames(pSound, &len) << std::endl;
}

//need to configure end_callback() with a sound config so we can know when the sound ends.

//ma_sound_set_end_callback()                             line 1488 in miniaudio.h
//to initialize sounds with configs, use "ma_sound_init_ex(&soundConfig, &sound)"