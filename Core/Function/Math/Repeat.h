/*
	����float��double����ȡ����
	����5 repeat 4.5 => 0.5
*/
inline real Repeat(real t, real length)
{
	return t - Floor(t / length) * length;
}
