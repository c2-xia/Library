#include "../defines.h"
#include "../Object/_vector3.h"
 
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
	return _Vector3(a.x*b,a.y*b,a.z*b);
}