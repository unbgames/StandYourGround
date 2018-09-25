#include "Rect.h"
#include <cstdlib>

Rect::Rect (float _x, float _y, float _w, float _h) :
    x(_x), y(_y), w(_w), h(_h){
}

bool Rect::Contains(float _x, float _y) const {
    return (_x >= x && _x <= x+w && _y >= y && _y <= y+h);
}

bool Rect::Contains(const Vec2 &a) const {
    return (a.GetX() >= x && a.GetX() <= x+w && a.GetY() >= y && a.GetY() <= y+h);
}

bool Rect::Intersect(const Rect &a) const {
    return x < a.GetRight() && this->GetRight() > a.GetLeft() &&
      this->GetTop() > a.GetBottom() && this->GetBottom() < a.GetTop();
}

Vec2 Rect::Center() const {
    return Vec2(x+w/2, y + h/2);
}

Vec2 Rect::BottomLeft() const {
    return Vec2(x, y+h);
}

Vec2 Rect::BottomRight() const {
    return Vec2(x+w, y+h);
}

Vec2 Rect::Origin() const {
    return Vec2(x, y);
}

void Rect::Shift(Vec2 v) {
    Shift(v.GetX(), v.GetY());
    // std::cout<<"POS:"<< Center() <<std::endl;
}

void Rect::Shift(float _x, float _y) {
    x += _x;
    y += _y;
}

void Rect::SetOrigin(Vec2 vec)  {
    SetOrigin(vec.GetX(), vec.GetY());
}

void Rect::SetOrigin(float _x, float _y)  {
    x = _x;
    y = _y;
}

void Rect::SetCenter(Vec2 vec)  {
    SetCenter(vec.GetX(), vec.GetY());
}

void Rect::SetCenter(float _x, float _y)  {
    x = _x - w/2;
    y = _y - h/2;
}

void Rect::SetSize(float _w, float _h)  {
    h = _h;
    w = _w;
}

void Rect::SetScale(Vec2 scale)  {
    SetScale(scale.GetX(), scale.GetY());
}

void Rect::SetScale(float sx, float sy)  {
    h *= sx;
    w *= sy;
}

void Rect::SetClip(float _x, float _y, float _w, float _h) {
    x = _x;
    y = _y;
    w = _x;
    h = _h;
}

float Rect::GetX() const {
    return x;
}

float Rect::GetLeft() const {
    return x;
}

float Rect::GetRight() const {
    return x + w;
}

float Rect::GetY() const {
    return y;
}

float Rect::GetTop() const {
    return y;
}

float Rect::GetBottom() const {
    return y + h;
}

float Rect::GetH() const {
    return h;
}

float Rect::GetW() const {
    return w;
}

float CenterDist(const Rect &a, const Rect &b) {
    auto vec = a.Center()-b.Center();
    return vec.Mag();
}

SDL_Rect Rect::toSDL() const {
    return SDL_Rect{int(x), int(y), int(w), int(h)};
}
