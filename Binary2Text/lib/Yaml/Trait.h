#ifndef TRAIT_H
#define TRAIT_H
#include <set>
#include <map>
template<class T>
class YAMLTraitBase
{
public:

	inline static bool ShouldSerializeArrayAsCompactString()
	{
		return false;
	}

	inline static bool IsBasicType()
	{
		return false;
	}

	template<class TransferFunction> inline
		static void Transfer(T& data, TransferFunction& transfer)
	{
		Trait<T>::transfer(transfer, data);
	}

	inline static void TransferStringToData(T& /*data*/, std::string& /*str*/)
	{
	}
};




template<class T>
class YAMLTraitsForBasicType : public YAMLTraitBase<T>
{
public:
	inline static bool ShouldSerializeArrayAsCompactString()
	{
		return true;
	}
	inline static bool IsBasicType()
	{
		return true;
	}
};

template<typename DataType>
struct Trait :public YAMLTraitBase<DataType>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, DataType& value)
	{
		value.Transfer(function);
	}
};

template<>
struct Trait<bool> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, bool& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<float> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, float& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<double> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, double& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt32> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt32& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt32> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt32& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt64> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt64& value)
	{
		function.transferBasicData(value);
	}
};
template<>
struct Trait<UInt64> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt64& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt16> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt16& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt16> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt16& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<SInt8> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, SInt8& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<UInt8> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, UInt8& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<char> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, char& value)
	{
		function.transferBasicData(value);
	}
};

template<>
struct Trait<std::string> :public YAMLTraitsForBasicType<bool>
{
	template<typename TransferFunction>
	inline	static void transfer(TransferFunction& function, std::string& value)
	{
		function.TransferStringData(value);
	}

	 
};





template<class T>
struct NonConstContainerValueType
{
	typedef typename T::value_type value_type;
};

template<class T>
struct NonConstContainerValueType<std::set<T> >
{
	typedef T value_type;
};

template<class T0, class T1, class Compare, class Allocator>
struct NonConstContainerValueType<std::map<T0, T1, Compare, Allocator> >
{
	typedef std::pair<T0, T1> value_type;
};

template<class T0, class T1, class Compare, class Allocator>
struct NonConstContainerValueType<std::multimap<T0, T1, Compare, Allocator> >
{
	typedef std::pair<T0, T1> value_type;
};
 
#endif
