#pragma once
#include <cmath>
#include "Object/_vector3.h"
inline float FloatMin(float a, float b)
{ 
	return std::fmin(a, b);
}

inline double FloatMin(double a, double b)
{
	return std::fmin(a, b);
}

inline int Min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

inline _Vector3 min(const _Vector3& lhs, const _Vector3& rhs) 
{
	return _Vector3(FloatMin(lhs.x, rhs.x), FloatMin(lhs.y, rhs.y), FloatMin(lhs.z, rhs.z)); 
}
