#include "Vec2.h"

#include <cmath>
Vec2::Vec2() : x(0), y(0){
}
Vec2::Vec2(std::initializer_list<float> initList) {
    if (initList.size() >= 2) {
        x = initList.begin()[0];
        y = initList.begin()[1];
    }
}

Vec2::Vec2 (float _x, float _y) : x(_x), y(_y){
}

void Vec2::Rotate(float rad) {
    float _x = std::cos(rad)*x - std::sin(rad)*y;
    float _y = std::sin(rad)*x + std::cos(rad)*y;
    x = _x;
    y = _y;
}
Vec2 Vec2::GetRotated(float rad) const {
    float _x = std::cos(rad)*x - std::sin(rad)*y;
    float _y = std::sin(rad)*x + std::cos(rad)*y;
    return Vec2(_x, _y);
}

float Vec2::Mag() const {
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

float Vec2::L0Mag() const {
    return std::abs(this->x) + std::abs(this->y);
}

void Vec2::SetMag(float newMag) {
    float mag = Mag();
    if (mag > 0) {
        x = newMag*x/mag;
        y = newMag*y/mag;
    }
}

float Vec2::EuclidianDist(const Vec2 &a, const Vec2 &b) {
    return std::sqrt(std::pow(a.x-b.x, 2) + std::pow(a.y-b.y, 2));
}

float Vec2::ManhattamDist(const Vec2 &a, const Vec2 &b) {
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

float Vec2::Angle(const Vec2 &a, const Vec2 &b) {
    return std::atan2(b.y-a.y, b.x - a.x);
}

float Vec2::GetX() const {
    return x;
}

float Vec2::GetY() const {
    return y;
}

void Vec2::Set(float _x, float _y) {
    x = _x;
    y = _y;
}

Vec2 Vec2::operator+(const Vec2 &a) const {
    return Vec2(a.x + x, a.y + y);
}

Vec2 Vec2::operator+(const Vec2 &&a) const {
    return Vec2(a.x + x, a.y + y);
}

Vec2 Vec2::operator-(const Vec2 &a) const {
    return Vec2(x - a.x, y - a.y);
}

Vec2 Vec2::operator-(const Vec2 &&a) const {
    return Vec2(x - a.x, y - a. y);
}

Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

Vec2& Vec2::operator+=(const Vec2 &a) {
    x += a.x;
    y += a.y;
    return *this;
}

Vec2& Vec2::operator+=(const Vec2 &&a) {
    x += a.x;
    y += a.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2 &a) {
    x -= a.x;
    y -= a.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2 &&a) {
    x -= a.x;
    y -= a.y;
    return *this;
}

Vec2& Vec2::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

bool Vec2::operator==(const Vec2 &a) {
    return (x == a.x && y == a.y);
}

Vec2  Vec2::operator*(float f) const {
    return Vec2(x*f, y*f);
}

Vec2  Vec2::operator/(float f) const {
    if (f != 0) {
        return Vec2(x/f, y/f);
    } else {
        return Vec2(x, y);
    }
}

std::ostream& operator<<(std::ostream& os, const Vec2& a) {
    os << '(' << a.x << ',' << a.y << ')';
    return os;
}
