#pragma once

#include <type_traits>

namespace sf
{
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>>
	struct Vector2
	{
		T x, y;

		Vector2() :
			x(0), y(0)
		{ /* Empty */ }

		Vector2(T x, T y) :
			x(x), y(y)
		{ /* Empty */ }

		Vector2(const Vector2& other) :
			x(other.x), y(other.y)
		{ /* Empty */ }


		//////////////////////// OPERATOR OVERLOADS ////////////////////////
		friend Vector2 operator-(const Vector2& other)
		{
			return Vector2(-other.x, -other.y);
		}

		friend Vector2 operator+(const Vector2& left, const Vector2& right)
		{
			return Vector2(left.x + right.x, left.y + right.y);
		}

		Vector2& operator+=(const Vector2& right)
		{
			x += right.x;
			y += right.y;
			return this;
		}

		friend Vector2 operator-(const Vector2& left, const Vector2& right)
		{
			return Vector2(left.x - right.x, left.y - right.y);
		}

		Vector2& operator-=(const Vector2& right)
		{
			x -= right.x;
			y -= right.y;
			return this;
		}

		friend Vector2 operator*(const Vector2& left, T right)
		{
			return Vector2(left.x * right, left.y * right);
		}

		friend Vector2 operator*(T left, const Vector2& right)
		{
			return Vector2(left * right.x, left * right.x);
		}

		Vector2& operator*=(T right)
		{
			x *= right;
			y *= right;
			return this;
		}

		friend Vector2 operator/(const Vector2& left, T right)
		{
			return Vector2(left.x / right, left.y / right);
		}

		Vector2& operator/=(T right)
		{
			x /= right;
			y /= right;
			return this;
		}
	};

	typedef Vector2<int>		Vector2i, Vec2i;
	typedef Vector2<unsigned>	Vector2u, Vec2u;
	typedef Vector2<float>		Vector2f, Vec2f;
	typedef Vector2<double>		Vector2d, Vec2d;
}