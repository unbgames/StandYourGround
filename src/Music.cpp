#include "../include/Music.h"
#include "../include/Resources.h"

#include <iostream>

Music::Music() : music(nullptr) {
}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}
Music::~Music() {
}

void Music::Play(int times) {
    if (music == nullptr) {
        std::cerr << "Error Music: There is no music to be played." << std::endl;
        return;
    }
    if (Mix_PlayMusic(music.get(), times) == -1) { // error
        std::cerr << "Error Music SDL(Play): " << Mix_GetError() <<std::endl;
        return;
    }
}

void Music::Stop(int msToStop) {
    if (Mix_PlayingMusic()) {
        Mix_FadeOutMusic(msToStop);
    } else {
        std::cerr << "Error Music SDL: There is no playing." << std::endl;
    }
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
    return (music != nullptr);
}
