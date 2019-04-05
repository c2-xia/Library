#ifndef YAML_WRITER_H
#define YAML_WRITER_H


#include "defines.h"
#include <string>
#include "extraFunction.h"
#include "../../Yaml/yaml-cpp/node/node.h"
#include "../../Yaml/yaml-cpp/emitter.h"
#include "../../Yaml/yaml-cpp/node/convert.h"
#include "../../Yaml/yaml-cpp/node/detail/impl.h"
#include "../../Yaml/yaml-cpp/node/emit.h"
#include "../../Yaml/yaml-cpp/node/impl.h"
#include "../../Yaml/yaml-cpp/node/iterator.h"
struct YamlWriter
{
	YamlWriter() :_pCashNode(NULL){};
	~YamlWriter();
	YAML::Node* _pCashNode;
	std::vector< YAML::Node*> willdeleteVector;
	int get(int oldID) { return 0; }

	void set(int oldID, int newID) { }
	int type()
	{
		return 1;//1 write,0 reader
	}
	template<typename T>
	void transfer(const char* name, T& value);

	template<typename T>
	void transfer(T& value);

	template<typename T>
	void transferBasicData(T& value);

	template<class T>
	void TransferStringData(T& data);

	void TransferStringToCurrentNode(const char* str);
	template<class T>
	void TransferSTLStyleArray(T& data);

	std::string toString()
	{
		if (_pCashNode)
			return YAML::Dump(*_pCashNode);
		else
			return "";
	}
};

template<class T>
inline void YamlWriter::TransferStringData(T& data)
{
	TransferStringToCurrentNode(data.c_str());
}

template<class T>
void YamlWriter::TransferSTLStyleArray(T& data)
{
	typedef typename NonConstContainerValueType<T>::value_type non_const_value_type;
	if (Trait<non_const_value_type>::ShouldSerializeArrayAsCompactString())
	{
#if UNITY_BIG_ENDIAN
#error "Needs swapping to be implemented to work on big endian platforms!"
#endif
		std::string str;
		size_t numElements = data.size();
		size_t numBytes = numElements * sizeof(non_const_value_type);
		str.resize(numBytes * 2);

		typename T::iterator dataIterator = data.begin();
		for (size_t i = 0; i < numElements; i++)
		{
			BytesToHexString((void*)&*dataIterator, sizeof(non_const_value_type), &str[i * 2 * sizeof(non_const_value_type)]);
			++dataIterator;
		}

		TransferStringData(str);
	}
	else
	{
		this->_pCashNode = new YAML::Node(YAML::NodeType::Sequence);
		this->willdeleteVector.push_back(this->_pCashNode);
		typename T::iterator i = data.begin();
		typename T::iterator end = data.end();
		while (i != end)
		{
			transfer("data", *i);
			++i;
		}
	}
}

template<typename T>
void YamlWriter::transfer(const char* name, T& value)
{
	YAML::Node* parent = NULL;
	if (_pCashNode == NULL)
	{
		parent = new YAML::Node(YAML::NodeType::Map);
		 
		this->willdeleteVector.push_back(parent);
	}		
	else
		parent = _pCashNode;

	_pCashNode = NULL;
	//把对象value的值传值给新的yaml节点，并赋值给cashNode
	Trait<T>::transfer(*this,value);
	//设置父子关系
	if (_pCashNode != parent && _pCashNode != NULL)
	{
		if (parent->IsMap())
		{
			(*parent)[name] = *_pCashNode;
		}
		else
		{
			(*parent).push_back(*_pCashNode);
		}
		
	}
	_pCashNode = parent;
}

template<typename T>
void YamlWriter::transfer(T& value)
{
	Trait<T>::transfer(*this, value);	 
}

 
#define EXPORTDLL __declspec(dllexport)
 
 
template<>
EXPORTDLL void YamlWriter::transferBasicData<SInt64>(SInt64& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<UInt64>(UInt64& data);
 

template<>
EXPORTDLL void YamlWriter::transferBasicData<float>(float& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<double>(double& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<char>(char& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<SInt8>(SInt8& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<UInt8>(UInt8& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<SInt32>(SInt32& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<UInt32>(UInt32& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<SInt16>(SInt16& data);

template<>
EXPORTDLL void YamlWriter::transferBasicData<UInt16>(UInt16& data);

#endif // !YAML_WRITER_H
