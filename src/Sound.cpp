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
            channel = Mix_PlayChannel(-1, chunk.get(), 0);
            Mix_Volume(channel, volume);
            started = true;
            // std::cerr<< "Sound at channel:"<<channel<<" at "<<&(*this)<<std::endl;
        }
    } else {
        std::cerr<< "No sound to be played"<<std::endl;
    }
}

bool Sound::Playing() {
    // std::cout<<"Channel:"<<channel<<std::endl;
    // std::cout<<"Ta tocando"<<(Mix_Playing(channel)?"True":"False")<<std::endl;
    return (Mix_Playing(channel) == 1);
}

void Sound::Stop() {
    if (chunk != nullptr && Playing()) {
        Mix_HaltChannel(channel);
        started = false;
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
