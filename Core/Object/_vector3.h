//vecotr3�ļ�����
struct _Vector3 {
	_Vector3():x(0),y(0),z(0)
	{ 
	}
	_Vector3(real xx,real yy,real zz):
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
};