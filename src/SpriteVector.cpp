#include "../include/SpriteVector.h"

SpriteVector::SpriteVector(GameObject& associated) : Component(associated), currentSprite("") {

}

void SpriteVector::AddSprite(std::string key, std::string file, int frameCount, float frameTime,
                       float secondsToSelfDestruct, Vec2 scale) {
    Sprite* spr = new Sprite(associated, file, frameCount, frameTime, secondsToSelfDestruct);
    if (spr == nullptr) {
        std::cout << "Falha ao abrir o arquivo " << file << std::endl;
    }
    spr->SetScale(scale.GetX(), scale.GetY());
    sprites[key] = spr;
    currentSprite = key;
}

void SpriteVector::SetCurSprite(std::string currentSprite) {
    if (sprites.find(currentSprite) == sprites.end()) {
        std::cout << "Tentando usar a sprite inexistente da key: " << currentSprite << std::endl;
    } else {
        this->currentSprite = currentSprite;
    }
}

Sprite * SpriteVector::SpriteVector::GetCurSprite() {
    if(sprites.find(currentSprite) == sprites.end()) {
        std::cout << "Tentando pegar sprite vazia de chave: " << currentSprite << std::endl;
    }
    return sprites[currentSprite];
}

bool SpriteVector::Is(std::string type) {
    return type == "SpriteVector";
}

std::string SpriteVector::Type() {
    return "SpriteVector";
}

void SpriteVector::Render() {
    GetCurSprite()->Render();
}

void SpriteVector::Render(float x, float y) {
    GetCurSprite()->Render(x, y);
}

void SpriteVector::Update(float dt) {
    GetCurSprite()->Update(dt);
}
