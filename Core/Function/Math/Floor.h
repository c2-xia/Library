/*
向下取整
*/
 
inline float Floorf(float f)
{
	// 使用 std::floor().
	// 目的是不丢失精度
	// 强转为int，然后当作float的值类返回，并没有什么用
	return floor(f);
}

inline double Floord(double f)
{
	// 使用 std::floor().
	// 目的是不丢失精度
	// 强转为int，然后当作double的值类返回，并没有什么用
	return floor(f);
}