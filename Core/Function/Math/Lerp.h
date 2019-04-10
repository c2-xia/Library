/*
根据参数t[0,1],在from和to之间取插值
比如当t=0.5时，在2和3之间取插值就是2.5
*/
 
inline float Lerp(float from, float to, float t)
{
	 return from + (to - from)*t;
}

inline double Lerp(double from, double to, double t)
{
	return from + (to - from)*t;
}

inline _Vector3 Lerp(_Vector3 from,_Vector3 to,real t)
{
	 return from + (to - from)*t;
}

#include "QuaternionFunction.h"
inline Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	Quaternion tmpQuat;
	// if (dot < 0), q1 and q2 are more than 360 deg apart.
	// The problem is that quaternions are 720deg of freedom.
	// so we - all components when lerping
	if (Dot(q1, q2) < 0.0F)
	{
		tmpQuat.x = q1.x + t * (-q2.x - q1.x);
		tmpQuat.y = q1.y + t * (-q2.y - q1.y);
		tmpQuat.z = q1.z + t * (-q2.z - q1.z);
		tmpQuat.w = q1.w + t * (-q2.w - q1.w);
	}
	else
	{
		tmpQuat.x = q1.x + t * (q2.x - q1.x);
		tmpQuat.y = q1.y + t * (q2.y - q1.y);
		tmpQuat.z = q1.z + t * (q2.z - q1.z);
		tmpQuat.w = q1.w + t * (q2.w - q1.w);
	}
	return Normalize(tmpQuat);
}