#ifndef VECTOR3_H
#define VECTOR3_H
//vecotr3µÄ¼òµ¥ÉùÃ÷
struct _Vector3 {
	typedef _Vector3 const & Arg;
	_Vector3() :x(0), y(0), z(0)
	{
	}
	_Vector3(real xx, real yy, real zz) :
		x(xx),
		y(yy),
		z(zz)
	{
	}
	union {
		struct {
			real x;
			real y;
			real z;
		};
		real coord[3];
	};

	friend _Vector3 operator -(const _Vector3& a, const _Vector3& b);

	friend _Vector3 operator +(const _Vector3& a, const _Vector3& b);

	friend _Vector3 operator *(const _Vector3& a, const  real b);

	friend _Vector3 operator / (const _Vector3& inV, const real s);

	bool operator == (const _Vector3& v);

	bool operator != (const _Vector3& v);

	_Vector3& operator += (const _Vector3& inV);
	_Vector3& operator -= (const _Vector3& inV);

	_Vector3& operator *= (const real s);

	_Vector3& operator /= (const real s);

	_Vector3 operator - ();
	static const float		epsilon;
};

const float	_Vector3::epsilon = 0.00001F;

_Vector3 operator -(const _Vector3& a, const _Vector3& b)
{
	return _Vector3(a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

_Vector3 operator +(const _Vector3& a, const _Vector3& b)
{
	return _Vector3(a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

_Vector3 operator *(const _Vector3& a, const  real b)
{
	return _Vector3(a.x*b, a.y*b, a.z*b);
}

_Vector3 operator / (const _Vector3& inV, const real s)
{
	_Vector3 temp(inV);
	temp.x /= s;
	temp.y /= s;
	temp.z /= s;
	return temp;
}

inline bool _Vector3::operator == (const _Vector3& v)
{
	return x == v.x && y == v.y && z == v.z;
}

inline bool _Vector3::operator != (const _Vector3& v)
{
	return x != v.x || y != v.y || z != v.z;
}

inline _Vector3& _Vector3::operator += (const _Vector3& inV)
{
	x += inV.x;
	y += inV.y;
	z += inV.z;
	return *this;
}
inline _Vector3& _Vector3::operator -= (const _Vector3& inV)
{
	x -= inV.x;
	y -= inV.y;
	z -= inV.z;
	return *this;
}

inline _Vector3& _Vector3::operator *= (const real s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

inline _Vector3& _Vector3::operator /= (const real s)
{
	Assert(s != 0.0f);
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

inline _Vector3 _Vector3::operator - ()
{
	return _Vector3(-x, -y, -z);
}
#endif
