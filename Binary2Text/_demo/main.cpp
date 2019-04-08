#include "relationdata2Text/Relationdata2Text.h"
#include "simpledata2Text/Simpledata2Text.h"
#include <string>
#include "lib/Yaml/extrafunction.h"
int main()
{
	Simpledata2Text::_Main();
	Realtiondata2Text::_Main();
	double data = 9999.123456789;
	char valueStr[64];
	if (DoubleToStringAccurate(data, valueStr, 64))
	{
		std::string t = std::to_string(data);
		char buffer_max[20];
		sprintf_s(buffer_max, "%f", data);
		int i = 0;
	}
}