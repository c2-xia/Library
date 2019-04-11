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

#include <vector>
#include <list>
#include <map>
template<class T>
inline void resize_trimmed(T& v, unsigned int sz)
{
	// the vector is growing
	if (sz > v.size())
	{
		if (sz != v.capacity())
		{
			T temp(v.get_allocator());
			temp.reserve(sz);
			temp.assign(v.begin(), v.end());
			temp.resize(sz);
			temp.swap(v);
		}
		else
			v.resize(sz);
	}
	// the vector is shrinking
	else if (sz < v.size())
	{
		T temp(v.begin(), v.begin() + sz, v.get_allocator());
		temp.swap(v);
	}
}
template<class T, class Allocator>
struct Trait<std::vector<T, Allocator>>  
{
	typedef std::vector<T, Allocator>	value_type;
	template<typename TransferFunction>
	inline static void transfer(TransferFunction& function, value_type& value)
	{
		function.TransferSTLStyleArray(value);
	} 
	static void ResizeSTLStyleArray(value_type& data, int rs) { resize_trimmed(data, rs); }
};


template<class T, class Allocator>
class Trait<std::list<T, Allocator> >  
{
public:
	typedef std::list<T, Allocator>	value_type;
 

		template<class TransferFunction> inline
		static void transfer(TransferFunction& function,value_type& data)
	{
		function.TransferSTLStyleArray(data);
	} 
	static void ResizeSTLStyleArray(value_type& data, int rs) { data.resize(rs); }
};


template<class FirstClass, class SecondClass>
class Trait<std::pair<FirstClass, SecondClass> >  
{
public: 
	typedef std::pair<FirstClass, SecondClass>	value_type;

	template<class TransferFunction> inline
		static void transfer(TransferFunction& function, value_type& data)
	{
		function.Transfer(data.first, "first");
		function.Transfer(data.second, "second");
	}
};


template<class FirstClass, class SecondClass, class Compare, class Allocator>
class Trait<std::map<FirstClass, SecondClass, Compare, Allocator> > 
{
public: 
	typedef std::map<FirstClass, SecondClass, Compare, Allocator>	value_type;

		template<class TransferFunction> inline
		static void transfer(TransferFunction& function, value_type& data)
	{
		//AssertIf(transfer.IsRemapPPtrTransfer() && SerializeTraits<FirstClass>::MightContainPPtr() && transfer.IsReadingPPtr());
			function.TransferSTLStyleMap(data);
	}
};



template<class FirstClass, class SecondClass, class Compare, class Allocator>
class Trait<std::multimap<FirstClass, SecondClass, Compare, Allocator> > 
{
public:

	typedef std::multimap<FirstClass, SecondClass, Compare, Allocator>	value_type;
		template<class TransferFunction> inline
		static void transfer(TransferFunction& function, value_type& data)
		{
			//AssertIf(transfer.IsRemapPPtrTransfer() && SerializeTraits<FirstClass>::MightContainPPtr() && transfer.IsReadingPPtr());
				function.TransferSTLStyleMap(data);
		}
};



template<class T, class Compare, class Allocator>
class Trait<std::set<T, Compare, Allocator> >
{
public:

	typedef std::set<T, Compare, Allocator>	value_type;
 

		template<class TransferFunction> inline
		static void transfer(TransferFunction& function, value_type& data)
		{
			//AssertIf(transfer.IsRemapPPtrTransfer() && transfer.IsReadingPPtr());
				function.TransferSTLStyleMap(data);
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
