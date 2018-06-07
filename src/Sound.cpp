#include <iostream>
#include <SDL2/SDL.h>

#include "../include/Resources.h"
#include "../include/Sound.h"

Sound::Sound(GameObject &associated, bool shouldReplay): Component(associated), started(false),
  chunk(nullptr), volume(MIX_MAX_VOLUME), channel(0), shouldReplay(shouldReplay) {
}

Sound::Sound(GameObject &associated, std::string file, bool shouldReplay) : Sound(associated, shouldReplay) {
    Open(file);
}

Sound::~Sound() {
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        if (shouldReplay) {
            Stop();
        }
        if (!started || !Playing()) {
            int channel = Mix_PlayChannel(-1, chunk.get(), 0);
            if (channel > -1) {
                Mix_Volume(channel, volume);
                started = true;
            }
            // std::cerr<< "Sound at channel:"<<channel<<" at "<<&(*this)<<std::endl;
        }
    } else {
        std::cerr<< "No sound to be played"<<std::endl;
    }
}

bool Sound::Playing() {
    // std::cout<<"Channel:"<<channel<<std::endl;
    // std::cout<<"Ta tocando"<<(Mix_Playing(channel)?"True":"False")<<std::endl;
    bool isPlaying = false;
    for (auto iter = channels.begin(); iter != channels.end();) {
        if (Mix_Playing(channels[*iter]) == 1) {
            isPlaying = true;
            ++iter;
        } else {
            channeld.erase(iter);
        }
    }
    return (started && isPlaying);
}

void Sound::Stop() {
    if (chunk != nullptr && Playing()) {
        // std::cout<<"Channel "<<channel<<" HALTED"<<std::endl;
        //
        for (const int &channel : channels) {
            Mix_HaltChannel(channel);
            started = false;
        }
        channels.clear();
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    // std::cerr<< "Carregou som at "<<&(*this)<<std::endl;
}

void Sound::SetVolume(unsigned int vol) {
    volume = vol;
    if (started && Playing()) {
        Mix_Volume(channel, volume);
    }
}

bool Sound::IsOpen() {
    return (chunk != nullptr);
}

void Sound::Update(float) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}

std::string Sound::Type() {
    return "Sound";
}
