#include "Relationdata2Text.h"
#include <string>

#include "defines.h"
#include "ReaderWriter/Trait.h"
#include "ReaderWriter/Yaml/YamlWriter.h"



 


namespace Realtiondata2Text
{ 
	struct Object
	{
		int id;

		template<typename TransferFunction>
		void Transfer(TransferFunction& transfer)
		{
			mTransfer(id);
		}
	};

	struct Student :public Object
	{
#define super Object 
		std::string name;
		int age;
		float height;

		template<typename TransferFunction>
		void Transfer(TransferFunction& transfer)
		{
			super::Transfer(transfer);
			mTransfer(name);
			mTransfer(age);
			mTransfer(height);
		}
	};
	//��ԭ���ݹ�ϵʱ���ϸ�ԭ�˶���Ĵ���˳���������ӵ�ʱ�򣬲�����ֿ�ֵ
	std::string toYaml(Student obj)
	{
		YamlWriter writer;
		writer.transfer("Student", obj);
		return writer.toString();
	}

	void _Main()
	{
		Student obj;
		obj.age = 20;
		obj.height = 180;
		obj.name = "xia";
		std::string result = toYaml(obj);
		
		int i = 0;
	}

}