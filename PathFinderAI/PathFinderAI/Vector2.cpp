#include "Vector2.h"
#include <cmath>


Vector2::Vector2(int x, int y)
{

    this->x = x;
    this->y = y;

}

float Vector2::GetMagnitude() const
{

    return sqrt(x * x + y * y);

}

Vector2 Vector2::Clamp(const Vector2& value, const Vector2& min, const Vector2& max)
{

    int X = value.x, Y = value.y;

    if (value.x <= min.x)
        X = min.x;

    if (value.x > max.x)
        X = max.x - 1;

    if (value.y <= min.y)
        Y = min.y;

    if (value.y > max.y)
        Y = max.y - 1;

    return Vector2(X, Y);

}

Vector2 Vector2::operator + (const Vector2& other) const
{

    return Vector2(x + other.x, y + other.y);

}

Vector2 Vector2::operator += (const Vector2& other) const
{

    return *this + other;

}

Vector2 Vector2::operator - (const Vector2& other) const
{

    return Vector2(x - other.x, y - other.y);

}

bool Vector2::operator == (const Vector2& other) const
{

    return x == other.x && y == other.y;

}

Vector2 Vector2::operator * (const float other) const
{

    return Vector2(x * other, y * other);

}

Vector2 Vector2::operator *= (const float other) const
{

    return (*this) * other;

}