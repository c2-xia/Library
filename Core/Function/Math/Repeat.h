/*
	用于float和double类型取余数
	比如5 repeat 4.5 => 0.5
*/
inline real Repeat(real t, real length)
{
	return t - Floor(t / length) * length;
}
