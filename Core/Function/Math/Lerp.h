/*
���ݲ���t[0,1],��from��to֮��ȡ��ֵ
���統t=0.5ʱ����2��3֮��ȡ��ֵ����2.5
*/

inline real Lerp(real from,real to,real t)
{
	 return from + (to - from)*t;
}

inline _Vector3 Lerp(_Vector3 from,_Vector3 to,real t)
{
	 return from + (to - from)*t;
}