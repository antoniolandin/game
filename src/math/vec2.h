#pragma once

#include <string>
#include <cmath>

class Vec2 {
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float xin, float yin);

    bool operator==(const Vec2& rhs) const;
    bool operator!=(const Vec2& rhs) const;

    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const Vec2& rhs) const;
    Vec2 operator/(const Vec2& rhs) const;

    void operator+=(const Vec2& rhs);
    void operator-=(const Vec2& rhs);
    void operator*=(const Vec2& rhs);
    void operator/=(const Vec2& rhs);

    void operator*=(const float scalar);
    void operator/=(const float scalar);

    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;

    void normalize();
    const std::string str() const;
    float squared_distance(const Vec2& rhs) const;
    float magnitude() const;
    void print() const;
};
