#ifndef YAML_READER_H
#define YAML_READER_H
#include "../../Yaml/yaml-cpp/Yaml.h"
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
struct YamlReader
{
	YamlReader(std::string& text):_pCashNode(NULL){
		root = YAML::Load(text);
	};
	YAML::Node root;
	YAML::Node* _pCashNode;
	std::map<int, int> remap;
	int get(int oldID)
	{
		return remap[oldID];
	}

	void set(int oldID,int newID)
	{
		remap[oldID] = newID;
	}

	int type()
	{
		return 0;//1 write,0 reader
	}

	template<typename T>
	void transfer(const char* name, T& value);

	template<typename T>
	void transfer(T& value);

	template<typename T>
	void transferBasicData(T& value);

	template<class T>
	void TransferStringData(T& data);
	 
	template<class T>
	void TransferSTLStyleArray(T& data);
};

template<typename T>
void YamlReader::transfer(const char* name, T& value)
{
	YAML::Node* parent = NULL;

	if (_pCashNode == NULL)
	{
		parent = &root;		 
	}
	else
		parent = _pCashNode;
	 
	_pCashNode = &(*parent)[name];
	Trait<T>::transfer(*this, value);
	_pCashNode = parent;
}

template<class T>
inline void YamlReader::TransferStringData(T& data)
{
	data = this->_pCashNode->Scalar().c_str();
}


template<class T>
inline void YamlReader::TransferSTLStyleArray(T& data)
{
	YAML::Node *parentNode = this->_pCashNode;
	typedef typename NonConstContainerValueType<T>::value_type non_const_value_type;

	switch (_pCashNode->Type())
	{
	case YAML::NodeType::value::Scalar:
	{
#if BIG_ENDIAN
#error "Needs swapping to be implemented to work on big endian platforms!"
#endif
		std::string str;
		TransferStringData(str);
		size_t byteLength = str.size() / 2;
		size_t numElements = byteLength / sizeof(non_const_value_type);
		Trait<T>::ResizeSTLStyleArray(data, numElements);
		typename T::iterator dataIterator = data.begin();
		for (size_t i = 0; i < numElements; i++)
		{
			HexStringToBytes(&str[i * 2 * sizeof(non_const_value_type)], sizeof(non_const_value_type), (void*)&*dataIterator);
			++dataIterator;
		}
	}
	break;

	case YAML::NodeType::value::Sequence:
	{  
		Trait<T>::ResizeSTLStyleArray(data, _pCashNode->size());
		typename T::iterator dataIterator = data.begin();

		YAML::Node * now_node = _pCashNode;
		for (auto it = now_node->begin(); it != now_node->end(); ++it)
		{
			_pCashNode = &(*it);
			Trait<non_const_value_type>::transfer( *this, *dataIterator);
			++dataIterator;
		}
	}
	break;

	// Some stupid old-style meta data writing code unnecessarily used mappings
	// instead of sequences to encode arrays. So, we're able to read that as well.
	case YAML::NodeType::value::Map:
	{
		/*yaml_node_pair_t* start = m_CurrentNode->data.mapping.pairs.start;
		yaml_node_pair_t* top = m_CurrentNode->data.mapping.pairs.top;

		SerializeTraits<T>::ResizeSTLStyleArray(data, top - start);
		typename T::iterator dataIterator = data.begin();

		for (yaml_node_pair_t* i = start; i != top; i++)
		{
			yaml_node_t* key = yaml_document_get_node(m_ActiveDocument, i->key);
			Assert(key->type == YAML_SCALAR_NODE);

			m_NodeName = (std::string)(char*)key->data.scalar.value;
			m_CurrentNode = yaml_document_get_node(m_ActiveDocument, i->value);

			YAMLSerializeTraits<non_const_value_type>::Transfer(*dataIterator, *this);
			++dataIterator;
		}*/
	}
	break;

	default:
		 Assert(false);
	}

	_pCashNode = parentNode;
}

template<typename T>
void YamlReader::transfer(T& value)
{
	Trait<T>::transfer(*this, value);
}


#define EXPORTDLL __declspec(dllexport)


template<>
EXPORTDLL void YamlReader::transferBasicData<bool>(bool& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<SInt64>(SInt64& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<UInt64>(UInt64& data);


template<>
EXPORTDLL void YamlReader::transferBasicData<float>(float& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<double>(double& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<char>(char& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<SInt8>(SInt8& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<UInt8>(UInt8& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<SInt32>(SInt32& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<UInt32>(UInt32& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<SInt16>(SInt16& data);

template<>
EXPORTDLL void YamlReader::transferBasicData<UInt16>(UInt16& data);


#endif 
