#pragma once
#include <cmath>
#include "Object/_vector3.h"
inline float FloatAbs(float a)
{
	return std::fabs(a);
}

inline float FloatAbs(double a)
{
	return std::fabs(a);
}

inline _Vector3 Abs(const _Vector3& v) 
{ 
	return _Vector3(FloatAbs(v.x), FloatAbs(v.y), FloatAbs(v.z));
}