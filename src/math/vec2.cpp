#include "vec2.h"
#include <iostream>

Vec2::Vec2() = default;

Vec2::Vec2(float xin, float yin)
: x(xin)
, y(yin)
{
}

bool Vec2::operator==(const Vec2& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
    return x != rhs.x || y != rhs.y;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
    return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
    return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::operator+=(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(const Vec2& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
}

void Vec2::operator/=(const Vec2& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
}

void Vec2::operator*=(float rhs)
{
    x *= rhs;
    y *= rhs;
}

void Vec2::operator/=(float rhs)
{
    x /= rhs;
    y /= rhs;
}

void Vec2::normalize()
{
    float magnitude = std::sqrt(x * x + y * y);
    x /= magnitude;
    y /= magnitude;
}

const std::string Vec2::str() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

float Vec2::squared_distance(const Vec2& rhs) const
{
    return std::pow(x - rhs.x, 2) + std::pow(y - rhs.y, 2);
}

float Vec2::magnitude() const
{
    return std::sqrt(x * x + y * y);
}

void Vec2::print() const
{
    std::cout << str() << std::endl;
}
