inline real Repeat(real t, real length)
{
	return t - Floor(t / length) * length;
}
