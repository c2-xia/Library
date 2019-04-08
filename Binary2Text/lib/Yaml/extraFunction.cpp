
#include "defines.h"

#include <cmath>
#include <limits>
#include <string>
#include "../3rd/gdtoa/gdtoa.h"

const int kMaxFloatDigits = (int)std::floor(std::numeric_limits<float>::digits * 3010.0f / 10000.0f + 2);
const int kMaxDoubleDigits = (int)std::floor(std::numeric_limits<double>::digits * 3010.0f / 10000.0f + 2);

bool FloatToStringAccurate(float f, char* buffer, size_t maximumSize)
{
	return g_ffmt(buffer, (float*)&f, kMaxFloatDigits, maximumSize) != NULL;
}

bool DoubleToStringAccurate(double f, char* buffer, size_t maximumSize)
{
	//经过测试，g_dfmt比标准库更加精确
	/*
		double data = 9999.123456789;
		char valueStr[64];
		if (DoubleToStringAccurate(data, valueStr, 64))
		{
			std::string t = std::to_string(data);
			char buffer_max[20];
			sprintf_s(buffer_max, "%f", data);
			int i = 0;
		}
		t 和 buffer_max 的值是"9999.123456789"，但是在debug模式下data的值是9999.1234567890006，
		最后面的0006被舍弃掉了。
		而 g_dfmt或者DoubleToStringAccurate 的输出就是"9999.1234567890006",是严格精确的
	*/
	return g_dfmt(buffer, (double*)&f, kMaxDoubleDigits, maximumSize) != NULL;
}

void HexStringToBytes(const char* str, size_t bytes, void *data)
{
	for (size_t i = 0; i < bytes; i++)
	{
		UInt8 b;
		char ch = str[2 * i + 0];
		if (ch <= '9')
			b = (ch - '0') << 4;
		else
			b = (ch - 'a' + 10) << 4;

		ch = str[2 * i + 1];
		if (ch <= '9')
			b |= (ch - '0');
		else
			b |= (ch - 'a' + 10);

		((UInt8*)data)[i] = b;
	}
}
float StringToFloatAccurate(const char* buffer)
{
	return strtof_gdtoa(buffer, NULL);
}

double StringToDoubleAccurate(const char* buffer)
{
	return strtod_gdtoa(buffer, NULL);
}

void BytesToHexString(const void *data, size_t bytes, char* str)
{
	static const char kHexToLiteral[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (size_t i = 0; i < bytes; i++)
	{
		UInt8 b = ((UInt8*)data)[i];
		str[2 * i + 0] = kHexToLiteral[b >> 4];
		str[2 * i + 1] = kHexToLiteral[b & 0xf];
	}
}

std::string BytesToHexString(const void* data, size_t numBytes)
{
	std::string result;
	result.resize(numBytes * 2);
	BytesToHexString(data, numBytes, &result[0]);
	return result;
}
 