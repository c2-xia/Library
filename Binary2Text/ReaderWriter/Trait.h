
template<typename DataType>
struct Trait
{
	template<typename TransferFunction> 
	inline static void transfer(TransferFunction& function, DataType& value)
	{
		value.Transfer(function);
	}
};

template<>
struct Trait<bool>
{
	template<typename TransferFunction> 
	inline static void transfer(TransferFunction& function, bool& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<float>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, float& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<double>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, double& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt32>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt32& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt32>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt32& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt64>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt64& value)
	{
		function.transferBasicData(value);
	}
};
template<>
struct Trait<UInt64>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt64& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt16>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt16& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt16>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt16& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt8>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt8& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt8>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt8& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<char>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, char& value)
	{
		function.transferBasicData(value);
	}
};
 
template<>
struct Trait<std::string>
{
	template<typename TransferFunction> 
	inline	static void transfer(TransferFunction& function, std::string& value)
	{
		function.TransferStringToCurrentNode(value.c_str());
	}
};