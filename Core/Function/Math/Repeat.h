/*
	����float��double����ȡ����
	����5 repeat 4.5 => 0.5
*/
inline float Repeatf(float t, float length)
{
	return t - Floorf(t / length) * length;
}

inline double Repeatd(double t, double length)
{
	return t - Floord(t / length) * length;
}
