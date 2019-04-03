/*
根据参数t[0,1],在from和to之间取插值
比如当t=0.5时，在2和3之间取插值就是2.5
*/

inline real Lerp(real from,real to,real t)
{
	 return from + (to - from)*t;
}

inline _Vector3 Lerp(_Vector3 from,_Vector3 to,real t)
{
	 return from + (to - from)*t;
}