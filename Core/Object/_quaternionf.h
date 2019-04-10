#ifndef QUATERNION_H
#define QUATERNION_H

//QuaternionµÄ¼òµ¥ÉùÃ÷
struct Quaternion {
	typedef Quaternion const & Arg;
	Quaternion();
	explicit Quaternion(real f);
	Quaternion(real x, real y, real z, real w);
	union {
		struct {
			real x;
			real y;
			real z;
			real w;
		};
		real coord[4];
	};

	const Quaternion & operator=(Quaternion::Arg v);
	const Quaternion & operator*=(real s);
	inline Quaternion&	Quaternion::operator /= (const real     	aScalar);
	const real& operator [] (int i)const { return coord[i]; }
	real& operator [] (int i) { return coord[i]; }

	static Quaternion identity() { return Quaternion(0.0F, 0.0F, 0.0F, 1.0F); }
};

inline Quaternion::Quaternion() {}
inline Quaternion::Quaternion(real f) : x(f), y(f), z(f), w(f) {}
inline Quaternion::Quaternion(real x, real y, real z, real w) : x(x), y(y), z(z), w(w) {}


inline const Quaternion & Quaternion::operator=(Quaternion::Arg v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
inline const Quaternion & Quaternion::operator*=(real s) {
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

inline Quaternion&	Quaternion::operator /= (const real     	aScalar)
{
	//AssertIf(CompareApproximately(aScalar, 0.0F));
	x /= aScalar;
	y /= aScalar;
	z /= aScalar;
	w /= aScalar;
	return *this;
}

#endif
