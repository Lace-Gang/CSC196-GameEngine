#pragma once
#include <cmath> //"c"math was their way of turning .h headers into files without ".h". I don't really know why they had to change it either

//math utils is a very common name because "math" is already a header in c++ (just like time)

//Putting these all in a new scope
//Namespaces! :D

namespace Math
{
	constexpr float Pi		= 3.14159265359f; //180 degrees
	constexpr float TwoPi	= 6.28318530718f; //360 degrees
	constexpr float HalfPi	= 1.57079632679f; //90 degrees
	//constexpr = "constant expresion" (converts at compile time rather than runtime if it has a constant as the input argument

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }



	float Sin(float radians)
	{
		return std::sinf(radians);
	}

	float Cos(float radians)
	{
		return std::cosf(radians);
	}

	
	//returns which ever one is larger
	template<typename T> //template is a variable type iiuc. Allows you to put in different types ao that you don't need to overload functions
	T Max(T a, T b)
	{
		return (a > b) ? a : b; //if a is greater than b, return a else return b (is what that means)
	}

	template<typename T> //has to be put for each function you use it in iiuc
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	T Abs(T value)
	{
		return (value < 0) ? -value : value;
		//value < 0 or value += (value * 2);
		
	}
}