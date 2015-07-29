#pragma once

template<class T>
class Vector2
{
public:
	T x;
	T y;

	Vector2(void)
		: x(0)
		, y(0)
	{}
	Vector2(const T &_x, const T &_y)
		: x(_x)
		, y(_y)
	{}
	Vector2(const Vector2 &other)
		: x(other.x)
		, y(other.y)
	{}

	Vector2 operator + (const Vector2 &rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator - (const Vector2 &rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	bool operator == (const Vector2 &rhs) const
	{
		// TODO : Explicit specialization for floating point
		// with epsilon.
		return x == rhs.x && y == rhs.y;
	}

	static Vector2<T> ZERO(void)
	{
		static Vector2 vec(0, 0);
		return vec;
	}

private:

};