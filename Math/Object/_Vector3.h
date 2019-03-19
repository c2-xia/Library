struct _Vector3 {

	union {
		struct {
			real x;
			real y;
			real z;
		};
		real coord[3];
	};
}