#ifndef VEC2_H
#define VEC2_H

#include <iostream>

class Vec2 {
public:
    Vec2();
    Vec2(float x, float y);
    void Rotate(float rad);
    Vec2 GetRotated(float rad) const;
    float Mag() const;
    void SetMag(float mag);
    static float EuclidianDist(const Vec2 &a, const Vec2 &b);
    static float ManhattamDist(const Vec2 &a, const Vec2 &b);
    static float Angle(const Vec2 &a, const Vec2 &b);

    float GetX() const;
    float GetY() const;
    void Set(float x, float y);

    Vec2 operator+(const Vec2 &a) const;
    Vec2 operator+(const Vec2 &&a) const;
    Vec2 operator-(const Vec2 &a) const;
    Vec2 operator-(const Vec2 &&a) const;
    Vec2 operator-() const;
    Vec2 operator*(float f) const;
    Vec2 operator/(float f) const;

    Vec2& operator=(const Vec2 &a) = default;
    Vec2& operator+=(const Vec2 &a);
    Vec2& operator+=(const Vec2 &&a);
    Vec2& operator-=(const Vec2 &a);
    Vec2& operator-=(const Vec2 &&a);
    Vec2& operator*=(float f);
    bool operator==(const Vec2 &a);
    friend std::ostream& operator<<(std::ostream& os, const Vec2& a);

private:
    float x;
    float y;
};

#endif /* VEC2_H */
