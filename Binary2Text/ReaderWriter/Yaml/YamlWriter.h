#ifndef YAML_WRITER_H
#define YAML_WRITER_H


#include "defines.h"
#include <string>
#include "../extraFunction.h"
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
	template<typename T>
	void transfer(const char* name, T& value);

	template<typename T>
	void transfer(T& value);

	template<typename T>
	void transferBasicData(T& value);

	void TransferStringToCurrentNode(const char* str);
	 
	std::string toString()
	{
		if (_pCashNode)
			return YAML::Dump(*_pCashNode);
		else
			return "";
	}
};




template<typename T>
void YamlWriter::transfer(const char* name, T& value)
{
	YAML::Node* parent = NULL;
	if (_pCashNode == NULL)
	{
		parent = new YAML::Node();
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
		(*parent)[name] = *_pCashNode;
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
