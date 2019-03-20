inline real Lerp(real from,real to,real t)
{
	 return from + (from -to)*t;
}

inline _Vector3 Lerp(_Vector3 from,_Vector3 to,real t)
{
	 return from + (from -to)*t;
}