#include "Simpledata2Text.h"
#include <string>

#include "defines.h"
#include "lib/Yaml/Trait.h"
#include "lib/Yaml/YamlWriter.h"
#include "lib/Yaml/YamlReader.h"


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

	void fromYaml(std::string text, Student& obj)
	{
		YamlReader reader(text);
		reader.transfer("Student", obj);
		 
	}

	void _Main()
	{
		Student obj;
		obj.age = 20;
		obj.height =180;
		obj.name = "xia";
		std::string result = toYaml(obj);	
		Student obj2;
		fromYaml(result,obj2);
		int i = 0;
	}
}