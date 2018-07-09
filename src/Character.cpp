#include "../include/Character.h"
#include "../include/SpriteVector.h"

Character::Character(GameObject& associated, const CharState &state) :
  Component(associated), hp(100), speed(100), state(state) {
}

bool Character::Is(std::string type) {
    return (type == "Character");
}

std::string Character::Type() {
    return "Character";
}
void Character::Render() {
}

void Character::Update(float dt) {
    // std::cerr << "Update Char" << std::endl;
    SpriteVector *sprVec = (SpriteVector *) associated.GetComponent("SpriteVector");
    if(sprVec != nullptr) {
        // std::cout << "CHAR UPDATE:"<<StateToString(state) << std::endl;
        sprVec->SetCurSprite(StateToString(state));
    }
}

CharState Character::GetState() const{
    // std::cout<<"Pegou state:"<<std::endl;
    return state;
}

void Character::HideSprite(bool hide) {
    SpriteVector *sprVec = (SpriteVector *) associated.GetComponent("SpriteVector");
    if(sprVec != nullptr) {
        if (hide) {
            sprVec->Hide();
        } else {
            sprVec->Show();
        }
    }
}

Vec2 Character::Origin() const {
    return associated.box.Origin();
}

Vec2 Character::BottomLeft() const {
    return associated.box.BottomLeft();
}

Vec2 Character::BottomRight() const {
    return associated.box.BottomRight();
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
    if(state.act == Action::no_action) {
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
    }
    else {
        switch(state.act) {
            case Action::atq:
                ret += "atq";
                break;
            case Action::pick:
                ret += "pick";
                break;
            case Action::cast:
                ret += "cast";
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
        std::cout << ret << std::endl;
    }
    // std::cout<<"STATE:"<<ret<<std::endl;
    return ret;
}
