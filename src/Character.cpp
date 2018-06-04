#include "../include/Character.h"

Character::Character(GameObject& associated, const CharState &state) :
  Component(associated), hp(100), speed(100), state(state) {
}

CharState Character::GetState() const{
    // std::cout<<"Pegou state:"<<std::endl;
    return state;
}

Vec2 Character::Origin() const {
    return associated.box.Origin();
}

void Character::AddSound(const std::string &key, const std::string &file) {
    Sound *sound = new Sound(associated, file, true);
    if (sound == nullptr) {
        std::cerr << "Tried to add sound, but is problebly does not exists: " << file << std::endl;
        exit(-1);
    }
    associated.AddComponent(sound);
    soundMap[key] = sound;
}

void Character::PlaySound(const std::string &key, int volume) {
    if (soundMap.find(key) != soundMap.end()) {
        soundMap[key]->SetVolume(volume);
        soundMap[key]->Play();
    } else {
        std::cerr << "Trying to play a sound not in the map: " << key << std::endl;
    }
}

std::string Character::StateToString(const CharState &state) {
    std::string ret;
    // std::cerr << "STAT MOVE:" <<((state.move == Movement::idle) ?"MOVE":"IDLE")<< std::endl;
    switch (state.move) {
        case Movement::idle:
            ret += "idle";
        break;
        case Movement::run:
            ret += "run";
        break;
    }
    ret += '_';
    switch (state.face) {
        case Facing::up:
            ret += "costa";
        break;
        case Facing::down:
            ret += "frente";
        break;
    }
    ret += '_';
    switch (state.dir) {
        case Direction::esq:
            ret += "esq";
        break;
        case Direction::dir:
            ret += "dir";
        break;
    }
    // std::cout<<"STATE:"<<ret<<std::endl;
    return ret;
}
