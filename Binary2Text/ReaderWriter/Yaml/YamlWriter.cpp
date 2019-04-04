#include "YamlWriter.h"
YamlWriter::~YamlWriter()
{
	for (size_t i = 0; i < this->willdeleteVector.size(); i++)
	{
		auto p_node =this->willdeleteVector[i];
		delete p_node;
	}
}

void YamlWriter::TransferStringToCurrentNode(const char* str)
{
	this->_pCashNode = new YAML::Node(YAML::NodeType::Scalar);
	(*this->_pCashNode) = str;
	this->willdeleteVector.push_back(this->_pCashNode);
}



template<>
inline void YamlWriter::transferBasicData<UInt64>(UInt64& data)
{
	char valueStr[17];
	BytesToHexString(&data, sizeof(UInt64), valueStr);
	valueStr[16] = '\0';
	TransferStringToCurrentNode(valueStr);
}


template<>
inline void YamlWriter::transferBasicData<float>(float& data)
{
	char valueStr[64];
	if (FloatToStringAccurate(data, valueStr, 64))
		TransferStringToCurrentNode(valueStr);
	else
		TransferStringToCurrentNode("error");
}

template<>
inline void YamlWriter::transferBasicData<double>(double& data)
{
	char valueStr[64];
	if (DoubleToStringAccurate(data, valueStr, 64))
		TransferStringToCurrentNode(valueStr);
	else
		TransferStringToCurrentNode("error");
}

template<>
inline void YamlWriter::transferBasicData<char>(char& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%hhd", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<SInt8>(SInt8& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%hhd", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<UInt8>(UInt8& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%hhu", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<SInt32>(SInt32& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%d", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<UInt32>(UInt32& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%u", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<SInt16>(SInt16& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%hd", data);
	TransferStringToCurrentNode(valueStr);
}

template<>
inline void YamlWriter::transferBasicData<UInt16>(UInt16& data)
{
	char valueStr[16];
	snprintf(valueStr, 16, "%hu", data);
	TransferStringToCurrentNode(valueStr);
}
template<>
void YamlWriter::transferBasicData<SInt64>(SInt64& data)
{
	char valueStr[17];
	BytesToHexString(&data, sizeof(SInt64), valueStr);
	valueStr[16] = '\0';
	TransferStringToCurrentNode(valueStr);
}
