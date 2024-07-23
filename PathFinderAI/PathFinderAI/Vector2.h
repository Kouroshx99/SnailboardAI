#pragma once
class Vector2
{

public:
	int x = 0;
	int y = 0;

	Vector2() = default;
	Vector2(int x, int y);

	float GetMagnitude() const;
	static Vector2 Clamp(const Vector2& value, const Vector2& min, const Vector2& max);

	Vector2 operator + (const Vector2& other) const;
	Vector2 operator += (const Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	bool operator == (const Vector2& other) const;
	Vector2 operator * (const float other) const;
	Vector2 operator *= (const float other) const;

};

