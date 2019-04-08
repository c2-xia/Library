#include "../../defines.h"
#include "../../Object/_vector3.h"
#include "../../Object/_quaternionf.h"
 
#pragma region
//Vector3  µÄoperatorº¯Êý
_Vector3 operator -(_Vector3& a, _Vector3& b)
{
	return _Vector3(a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

_Vector3 operator +(_Vector3& a, _Vector3& b)
{
	return _Vector3(a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

_Vector3 operator *(_Vector3& a, real b)
{
	return _Vector3(a.x*b, a.y*b, a.z*b);
}

_Vector3 operator / (const _Vector3& inV, const float s)
{
	_Vector3 temp(inV);
	temp.x /= s;
	temp.y /= s;
	temp.z /= s;
	return temp;
}

bool operator == (const _Vector3& _this, const _Vector3& v)
{
	return _this.x == v.x && _this.y == v.y && _this.z == v.z;
}

bool operator != (const _Vector3& _this, const _Vector3& v)
{
	return _this.x != v.x || _this.y != v.y || _this.z != v.z;
}

_Vector3& operator += (_Vector3& _this, const _Vector3& inV)
{
	_this.x += inV.x;
	_this.y += inV.y;
	_this.z += inV.z;
	return _this;
}
_Vector3& operator -= (_Vector3& _this, const _Vector3& inV)
{
	_this.x -= inV.x;
	_this.y -= inV.y;
	_this.z -= inV.z;
	return _this;
}

_Vector3& operator *= (_Vector3& _this, float s)
{
	_this.x *= s;
	_this.y *= s;
	_this.z *= s;
	return _this;
}

_Vector3& operator /= (_Vector3& _this, float s)
{
	//DebugAssertIf(CompareApproximately(s, 0.0F));
	_this.x /= s;
	_this.y /= s;
	_this.z /= s;
	return _this;
}

_Vector3 operator - (const _Vector3& _this)
{
	return _Vector3(-_this.x, -_this.y, -_this.z);
}

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

float Dot(const _Vector3& lhs, const _Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float SqrMagnitude(const _Vector3& inV)
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
real Vector3_epsilon = 0.00001F;

inline _Vector3 NormalizeSafe(const _Vector3& inV, const _Vector3& defaultV = Vector3_zero)
{
	float mag = Magnitude(inV);
	if (mag > Vector3_epsilon)
		return inV / Magnitude(inV);
	else
		return defaultV;
}

#pragma endregion

