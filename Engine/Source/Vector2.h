#pragma once
#include <cmath> //necessary to get a square root for the length function

//any 2d game is going to have a vector2 class
//3d games would have a vector3 class

//Struct means default access level is public
struct Vector2
{
	float x;
	float y;
	
	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	Vector2 Add(Vector2 v) { return Vector2{x + v.x, y +v.y}; }
	//{} is innitializers

	//operator overloading!!! :D
	//also, the const makes it so that this does not change our object instance at all
	Vector2 operator + ( Vector2 v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (Vector2 v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (Vector2 v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (Vector2 v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

	float LengthSqr() { return (x * x) + (y * y); }
	float Length() { return std::sqrt((x * x) + (y * y)); }
};