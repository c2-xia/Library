#pragma once
#include "defines.h"
#include "Object/_vector3.h"


_Vector3& Scale(_Vector3& _this, const _Vector3& inV)
{
	_this.x *= inV.x;
	_this.y *= inV.y;
	_this.z *= inV.z;
	return _this;
}

_Vector3 Cross(const _Vector3& lhs, const _Vector3& rhs)
{
	return _Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);
}

real Dot(const _Vector3& lhs, const _Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

real SqrMagnitude(const _Vector3& inV)
{
	return Dot(inV, inV);
}


#include <cmath>
inline float Magnitude(const _Vector3& inV)
{
	return sqrt(Dot(inV, inV));
}

inline _Vector3 Normalize(const _Vector3& inV)
{
	return inV / Magnitude(inV);
}


_Vector3 Vector3_zero;
 

inline _Vector3 NormalizeSafe(const _Vector3& inV, const _Vector3& defaultV = Vector3_zero)
{
	float mag = Magnitude(inV);
	if (mag > _Vector3::epsilon)
		return inV / Magnitude(inV);
	else
		return defaultV;
} 

inline _Vector3 Project(const _Vector3& v1, const _Vector3& v2)
{ 
	return v2 * Dot(v1, v2) / Dot(v2, v2);
}

bool CompareApproximately(const _Vector3& inV0, const _Vector3& inV1, const float inMaxDist = _Vector3::epsilon)
{ 
	return SqrMagnitude(inV1 - inV0) < inMaxDist * inMaxDist;
}