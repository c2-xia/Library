#pragma once
#include "defines.h"
#include "Object/_vector3.h"
#include "Object/_quaternionf.h"

inline Quaternion mul(Quaternion::Arg a, Quaternion::Arg b)
{
	return Quaternion(
		+a.x*b.w + a.y*b.z - a.z*b.y + a.w*b.x,
		-a.x*b.z + a.y*b.w + a.z*b.x + a.w*b.y,
		+a.x*b.y - a.y*b.x + a.z*b.w + a.w*b.z,
		-a.x*b.x - a.y*b.y - a.z*b.z + a.w*b.w);
}

inline Quaternion mul(Quaternion::Arg a, _Vector3::Arg b)
{
	return Quaternion(
		+a.y*b.z - a.z*b.y + a.w*b.x,
		-a.x*b.z + a.z*b.x + a.w*b.y,
		+a.x*b.y - a.y*b.x + a.w*b.z,
		-a.x*b.x - a.y*b.y - a.z*b.z);
}

inline Quaternion mul(_Vector3::Arg a, Quaternion::Arg b)
{
	return Quaternion(
		+a.x*b.w + a.y*b.z - a.z*b.y,
		-a.x*b.z + a.y*b.w + a.z*b.x,
		+a.x*b.y - a.y*b.x + a.z*b.w,
		-a.x*b.x - a.y*b.y - a.z*b.z);
}

inline Quaternion operator *(Quaternion::Arg a, Quaternion::Arg b)
{
	return mul(a, b);
}

inline Quaternion operator *(Quaternion::Arg a, _Vector3::Arg b)
{
	return mul(a, b);
}

inline Quaternion operator *(_Vector3::Arg a, Quaternion::Arg b)
{
	return mul(a, b);
}
inline Quaternion	operator / (const Quaternion& q, const real s)
{
	Quaternion t(q);
	return t /= s;
}



inline float Dot(const Quaternion& q1, const Quaternion& q2)
{
	return (q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w);
}

inline float SqrMagnitude(const Quaternion& q)
{
	return Dot(q, q);
}

#include <cmath>
inline float Magnitude(const Quaternion& q)
{
	return sqrt(SqrMagnitude(q));
}

inline Quaternion Normalize(const Quaternion& q)
{
	return q / Magnitude(q); 
}

inline Quaternion NormalizeSafe(const Quaternion& q)
{
	float mag = Magnitude(q);
	if (mag < _Vector3::epsilon)
		return Quaternion::identity();
	else
		return q / mag;
}
  
 
