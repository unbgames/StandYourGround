#include <iostream>

#include "../include/Game.h"
#include "../include/Resources.h"


std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    if (Resources::imageTable.find(file) != Resources::imageTable.end()) {
        return Resources::imageTable[file];
    } else {
        const char *dir = file.c_str();
        auto renderer = Game::GetInstance().GetRenderer();
        // std::cout << "Renderer: " << renderer << std::endl;
        // std::cout << "Dir: " << dir << std::endl;
        SDL_Texture* texture = IMG_LoadTexture(renderer, dir);
        std::shared_ptr<SDL_Texture> texture_ptr(texture,
            [] (SDL_Texture *tex) {
                SDL_DestroyTexture(tex);
            }
        );

        if (texture_ptr == nullptr) { // error
            std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
            return nullptr;
        } else {
            std::cout << "Added Image"<<std::endl;
            Resources::imageTable.insert({file, texture_ptr});
            return Resources::imageTable[file];
        }
    }
}

void Resources::ClearImages() {
    auto it = Resources::imageTable.begin();
    while (it != Resources::imageTable.end()) {
        if (it->second.use_count() == 1) {
            it = Resources::imageTable.erase(it);
        } else {
            it++;
        }
    }
    // Resources::imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    if (Resources::musicTable.find(file) != Resources::musicTable.end()) {
        return Resources::musicTable[file];
    } else {
        Mix_Music* music = Mix_LoadMUS(file.c_str());
        std::shared_ptr<Mix_Music> music_ptr(music,
            [] (Mix_Music *m) {
                Mix_FreeMusic(m);
            }
        );
        if (music_ptr  == nullptr) {
            std::cerr << "Error Music SDL(Open): " << Mix_GetError() <<std::endl;
            return nullptr;
        } else {
            Resources::musicTable.insert({file, music_ptr});
            std::cout << "Added Music"<<std::endl;
            return Resources::musicTable[file];
        }
    }
}

void Resources::ClearMusic() {
    auto it = Resources::musicTable.begin();
    while (it != Resources::musicTable.end()) {
        if (it->second.use_count() == 1) {
            it = Resources::musicTable.erase(it);
        } else {
            it++;
        }
    }
    // Resources::musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    if (Resources::soundTable.find(file) != Resources::soundTable.end()) {
        return Resources::soundTable[file];
    } else {
        std::shared_ptr<Mix_Chunk> sound(Mix_LoadWAV(file.c_str()),
            [] (Mix_Chunk *s) {
                Mix_FreeChunk(s);
            });
        if (sound == nullptr) {
            std::cerr<< "Failed to open WAV"<<std::endl;
            return nullptr;
        } else {
            std::cout << "Added Sound"<<std::endl;
            Resources::soundTable.insert({file, sound});
            return Resources::soundTable[file];
        }
    }
}

void Resources::ClearSound() {
    auto it = Resources::soundTable.begin();
    // std::cout << "Size:"<<  Resources::soundTable.size()<<std::endl;
    while (it != Resources::soundTable.end()) {
        if (it->second.use_count() == 1) {
            it = Resources::soundTable.erase(it);
        } else {
            it++;
        }
    }
    // Resources::soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
    std::string key = file + std::to_string(size);
    if (Resources::fontTable.find(key) != Resources::fontTable.end()) {
        return Resources::fontTable[key];
    } else {
        std::shared_ptr<TTF_Font> sound(TTF_OpenFont(file.c_str(), size),
            [] (TTF_Font *s) {
                TTF_CloseFont(s);
            });
        if (sound == nullptr) {
            std::cerr<< "Failed to open font"<<std::endl;
            return nullptr;
        } else {
            std::cout << "Added Font"<<std::endl;
            Resources::fontTable.insert({key, sound});
            return Resources::fontTable[key];
        }
    }
}

void Resources::ClearFont() {
    auto it = Resources::fontTable.begin();
    // std::cout << "Size:"<<  Resources::fontTable.size()<<std::endl;
    while (it != Resources::fontTable.end()) {
        if (it->second.use_count() == 1) {
            it = Resources::fontTable.erase(it);
        } else {
            it++;
        }
    }
}

void Resources::Clear() {
    Resources::ClearImages();
    Resources::ClearMusic();
    Resources::ClearSound();
    Resources::ClearFont();
}
