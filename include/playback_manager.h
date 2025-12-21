#include "miniaudio.h"
#include <iostream>

class PlaybackManager {
    private: 
        ma_engine engine;
        ma_sound sound;
        ma_result result;

    public:
        PlaybackManager();
        ~PlaybackManager();

        void Play();
        void Play(const char* file);
        void Stop();

        // ma_sound_seek_to_pcm_frame(&sound, 0); SEEKS sound back to beginning
        // ma_sound_set_start_time_in_pcm_frames(&sound, ma_engine_get_time_in_pcm_frames(&engine) + (ma_engine_get_sample_rate(&engine) * 2));

};