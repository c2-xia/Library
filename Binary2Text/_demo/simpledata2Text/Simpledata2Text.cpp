#include "Simpledata2Text.h"
#include <string>

#include "defines.h"
#include "ReaderWriter/Trait.h"
#include "ReaderWriter/Yaml/YamlWriter.h"

 
struct Student
{ 
	std::string name;
	int age;
	float height;

	template<typename TransferFunction>
	void Transfer(TransferFunction& transfer)
	{
		mTransfer(name);
		mTransfer(age);
		mTransfer(height);
	}
};

namespace Simpledata2Text
{
	std::string toYaml(Student obj)
	{
		YamlWriter writer;
		writer.transfer("Student",obj);
		return writer.toString();
	}

	void _Main()
	{
		Student obj;
		obj.age = 20;
		obj.height =180;
		obj.name = "xia";
		std::string result = toYaml(obj);
		
		int i = 0;
	}
}