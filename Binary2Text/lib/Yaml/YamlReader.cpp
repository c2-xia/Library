#include "YamlReader.h"
 

 

template<>
inline void YamlReader::transferBasicData<bool>(bool& data)
{
	int i;
	sscanf(this->_pCashNode->Scalar().c_str(), "%d", &i);
	data = (i == 0);
}

template<>
inline void YamlReader::transferBasicData<UInt64>(UInt64& data)
{
	HexStringToBytes(this->_pCashNode->Scalar().c_str(), sizeof(UInt64), &data);
}


template<>
inline void YamlReader::transferBasicData<float>(float& data)
{
	data = StringToFloatAccurate(this->_pCashNode->Scalar().c_str());
}

template<>
inline void YamlReader::transferBasicData<double>(double& data)
{
	data = StringToDoubleAccurate(this->_pCashNode->Scalar().c_str());
}

template<>
inline void YamlReader::transferBasicData<char>(char& data)
{
	int i;
	sscanf(this->_pCashNode->Scalar().c_str(), "%d", &i);
	data = i;
}

template<>
inline void YamlReader::transferBasicData<SInt8>(SInt8& data)
{
	transferBasicData(reinterpret_cast<char&> (data));
}

template<>
inline void YamlReader::transferBasicData<UInt8>(UInt8& data)
{
	unsigned int i;
	sscanf(this->_pCashNode->Scalar().c_str(), "%u", &i);
	data = i;
}

template<>
inline void YamlReader::transferBasicData<SInt32>(SInt32& data)
{
	sscanf(this->_pCashNode->Scalar().c_str(), "%d", &data);
}

template<>
inline void YamlReader::transferBasicData<UInt32>(UInt32& data)
{
	sscanf(this->_pCashNode->Scalar().c_str(), "%u", &data);
}

template<>
inline void YamlReader::transferBasicData<SInt16>(SInt16& data)
{
	sscanf(this->_pCashNode->Scalar().c_str(), "%hd", &data);
}

template<>
inline void YamlReader::transferBasicData<UInt16>(UInt16& data)
{
	sscanf(this->_pCashNode->Scalar().c_str(), "%hu", &data);
}
template<>
void YamlReader::transferBasicData<SInt64>(SInt64& data)
{ 
	HexStringToBytes(this->_pCashNode->Scalar().c_str(), sizeof(SInt64), &data);
}
