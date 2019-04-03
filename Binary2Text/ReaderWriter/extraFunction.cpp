
#include "defines.h"

#include <cmath>
#include <limits>
#include <string>
#include "../3rd/gdtoa/gdtoa.h"

const int kMaxFloatDigits = std::floor(std::numeric_limits<float>::digits * 3010.0 / 10000.0 + 2);
const int kMaxDoubleDigits = std::floor(std::numeric_limits<double>::digits * 3010.0 / 10000.0 + 2);

bool FloatToStringAccurate(float f, char* buffer, size_t maximumSize)
{
	return g_ffmt(buffer, (float*)&f, kMaxFloatDigits, maximumSize) != NULL;
}

bool DoubleToStringAccurate(double f, char* buffer, size_t maximumSize)
{
	return g_dfmt(buffer, (double*)&f, kMaxDoubleDigits, maximumSize) != NULL;
}

void HexStringToBytes(char* str, size_t bytes, void *data)
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
 