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
        float cur_sound_length;
        float cur_sound_time;

        void Play();
        void Play(const char* file, const char* f_name);
        void Stop();
        void SeekTo(float time, bool continue_play);
        bool IsPlaying();

        ma_sound* GrabSound();
        float GrabTime();

        // ma_sound_seek_to_pcm_frame(&sound, 0); SEEKS sound back to beginning
        // ma_sound_set_start_time_in_pcm_frames(&sound, ma_engine_get_time_in_pcm_frames(&engine) + (ma_engine_get_sample_rate(&engine) * 2));

};