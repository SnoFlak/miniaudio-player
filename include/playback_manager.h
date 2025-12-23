#include "miniaudio.h"
#include <iostream>

class PlaybackManager {
    private: 
        ma_engine engine;
        ma_sound sound;
        ma_sound_config sound_config;
        ma_result result;

    public:
        PlaybackManager();
        ~PlaybackManager();

        const char* file_name;

        void Play();
        void Play(const char* file, const char* f_name);
        void Stop();
        bool IsPlaying();

        // ma_sound_seek_to_pcm_frame(&sound, 0); SEEKS sound back to beginning
        // ma_sound_set_start_time_in_pcm_frames(&sound, ma_engine_get_time_in_pcm_frames(&engine) + (ma_engine_get_sample_rate(&engine) * 2));

};