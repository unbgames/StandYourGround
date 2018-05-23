#include <iostream>
#include <SDL2/SDL.h>

#include "../include/Resources.h"
#include "../include/Sound.h"

Sound::Sound(GameObject &associated): Component(associated), chunk(nullptr) {
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
}

void Sound::Play(int times) {
    if (chunk != nullptr) {
        if (!Playing()) {
            channel = Mix_PlayChannel(-1, chunk.get(), 0);
            // std::cerr<< "Sound at channel:"<<channel<<" at "<<&(*this)<<std::endl;
        }
    } else {
        std::cerr<< "No sound to be played"<<std::endl;
    }
}

bool Sound::Playing() {
    //std::cout<<"Ta tocando"<<(Mix_Playing(channel)?"True":"False")<<std::endl;
    return (Mix_Playing(channel) == 1);
}

void Sound::Stop() {
    if (chunk == nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    // std::cerr<< "Carregou som at "<<&(*this)<<std::endl;
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
