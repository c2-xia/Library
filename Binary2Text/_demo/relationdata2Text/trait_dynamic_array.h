#include "../ReaderWriter/Trait.h"
#include "dynamic_array.h"
template<class T, size_t align>
struct Trait<dynamic_array<T, align>>
{
	typedef dynamic_array<T, align>	value_type;
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, dynamic_array<T, align>& value)
	{
		function.TransferSTLStyleArray(value);
	}
};