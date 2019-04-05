#ifndef EXTRA_FUNCTION
#define EXTRA_FUNCTION 
void BytesToHexString(const void *data, size_t bytes, char* str);
std::string BytesToHexString(const void* data, size_t numBytes);
void HexStringToBytes(const char* str, size_t bytes, void *data);
bool DoubleToStringAccurate(double f, char* buffer, size_t maximumSize);
bool FloatToStringAccurate(float f, char* buffer, size_t maximumSize);
float StringToFloatAccurate(const char* buffer);
double StringToDoubleAccurate(const char* buffer);
#endif