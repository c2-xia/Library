//QuaternionµÄ¼òµ¥ÉùÃ÷
struct _Quaternion {
	_Quaternion() :x(0), y(0), z(0),w(1)
	{
	}
	_Quaternion(real xx, real yy, real zz,real ww) :
		x(xx),
		y(yy),
		z(zz),
		w(ww)
	{
	}
	union {
		struct {
			real x;
			real y;
			real z;
			real w;
		};
		real coord[4];
	};

};