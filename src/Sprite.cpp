#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <iostream>
#include <SDL2/SDL_image.h>

Sprite::Sprite(GameObject &associated, int frameCount, float frameTime, float secondsToSelfDestruct) :
    Component(associated), texture(nullptr), scale(1, 1), frameCount(frameCount), currentFrame(0),
    frameTime(frameTime), secondsToSelfDestruct(secondsToSelfDestruct), hide(false), offset({0, 0}),
    opacity(255) {
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount, float frameTime,
    float secondsToSelfDestruct) :
    Sprite(associated, frameCount, frameTime, secondsToSelfDestruct) {
    Open(file);
}

Sprite::~Sprite() {
    std::cout << "DELETOU SPRITE" << std::endl;
}

int Sprite::GetWidth() {
    return width*scale.GetX();
}

int Sprite::GetHeight() {
    // std::cerr << "Factor Y:"<< scale.GetY()<< std::endl;
    return height*scale.GetY();
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

std::string Sprite::Type() {
    return "Sprite";
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    int w, h;
    if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h) != 0) { // error
        SDL_DestroyTexture(texture.get());
        // std::cerr << "Error Sprite SDL: " << SDL_GetError() << std::endl;
        return;
    }
    height = h;
    width = w / frameCount;
    SetClip(0, 0, width, height);
}

void Sprite::Render() {
    if(!hide) {
        Vec2 camPos = Camera::pos;
        Render(associated.box.GetX() + camPos.GetX() + offset.GetX(), associated.box.GetY() + camPos.GetY() + offset.GetY());
    }
}

void Sprite::Render(float x, float y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w * scale.GetX();
    dstRect.h = clipRect.h * scale.GetY();

    // std::cout << "Render at (" << x<<','<< y<<')';
    // std::cout << "Size as (" << dstRect.h <<','<< dstRect.w <<')';
    if (texture == nullptr) {
        std::cerr << "Error Sprite: Trying to render null texture." <<std::endl;
    }
    SDL_SetTextureAlphaMod(texture.get(), opacity);
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angle*180/PI,
        nullptr, SDL_FLIP_NONE);
    SDL_SetTextureAlphaMod(texture.get(), 255);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}

void Sprite::SetClip(Rect rec) {
    clipRect.x = rec.GetX();
    clipRect.y = rec.GetY();
    clipRect.h = rec.GetH();
    clipRect.w = rec.GetW();
}

Rect Sprite::GetClip() {
    return Rect(clipRect.x, clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetScale (float scaleX, float scaleY) {
    if (scaleX != 0 && scaleY != 0) {
        scale.Set(scaleX, scaleY);
    }
}

void Sprite::SetScale (Vec2 scale) {
    SetScale(scale.GetX(), scale.GetY());
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::Update(float dt) {
    if (frameTime > 0) {
        timer.Update(dt);
        if (timer.Get() >= frameTime) {
            timer.Restart();
            currentFrame++;
            if(currentFrame >= frameCount) {
                currentFrame = 0;
            }
            SetFrame(currentFrame);
        }
    }
    /*if (secondsToSelfDestruct != 0) {
        if (timer.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        } else {
            long frame = static_cast<long>(std::floor(timer.Get()*1000/frameTime));

            clipRect.x = (frame%frameCount)*width;
        }
    } else {

        long frame = static_cast<long>(std::floor(timer.Get()*1000/frameTime));

        // if (frameCount == 3) std::cout<<"Elapsed:"<<timeElapsed<<" dt:"<<dt<<" Frame:"<<frame<<std::endl;
        clipRect.x = (frame%frameCount)*width;

    }*/
}


void Sprite::SetFrame(int frame) {
    SetClip((width)*frame, 0, clipRect.w, clipRect.h);
}

void Sprite::SetOffset(Vec2 offset) {
    this->offset.Set(offset.GetX(), offset.GetY());
}

void Sprite::Hide() {
    hide = true;
}

void Sprite::Show() {
    hide = false;
}

void Sprite::Opacity(float percent) {
    if (percent >= 0 && percent <= 100) {
        opacity = std::floor(percent * 255 / 100);
    }
}
