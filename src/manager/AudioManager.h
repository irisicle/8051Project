//
// Created by Iris Chow on 2026-04-07.
//

#ifndef INC_8051PROJECT_AUDIOMANAGER_H
#define INC_8051PROJECT_AUDIOMANAGER_H

#include <unordered_map>
#include "SDL3_mixer/SDL_mixer.h"

class AudioManager {

    MIX_Mixer* mixer = nullptr;
    MIX_Track* musicTrack = nullptr;
    static MIX_Track* sfxTrack;
    static std::unordered_map<std::string, MIX_Audio*> audio;

public:
    AudioManager();

    void loadAudio(const std::string& name, const char* path) const;
    void playMusic(const std::string& name) const;
    void stopMusic() const;

    static void playSfx(const std::string& name);
};

#endif //INC_8051PROJECT_AUDIOMANAGER_H