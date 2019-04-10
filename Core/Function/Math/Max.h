#pragma once
#include <cmath>
#include "Object/_vector3.h"
inline float FloatMax(float a, float b)
{
	return std::fmax(a, b);
}

inline double FloatMax(double a, double b)
{
	return std::fmax(a, b);
}

inline int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


inline _Vector3 max(const _Vector3& lhs, const _Vector3& rhs) 
{
	return _Vector3(FloatMax(lhs.x, rhs.x), FloatMax(lhs.y, rhs.y), FloatMax(lhs.z, rhs.z)); 
}
