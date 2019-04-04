#include "Relationdata2Text.h"
#include <string>

#include "defines.h"
#include "ReaderWriter/Trait.h"
#include "trait_dynamic_array.h"
#include "ReaderWriter/Yaml/YamlWriter.h"



#include "dynamic_array.h"

 


namespace Realtiondata2Text
{ 
	static int ID = 0;
	struct Object
	{
		int id;
		Object()
		{
			this->id = ID++;
		};
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
		Student():Object()
		{

		}
		template<typename TransferFunction>
		void Transfer(TransferFunction& transfer)
		{
			super::Transfer(transfer);
			mTransfer(name);
			mTransfer(age);
			mTransfer(height);
		}
	};

	struct ObjectRef
	{
		int refrenceID;
		template<typename TransferFunction>
		void Transfer(TransferFunction& transfer)
		{ 
			mTransfer(refrenceID);
		}
	};

	struct ClassRoom :public Object
	{
		ClassRoom() :Object()
		{ 
		}
		void addStudent(Student& pStudent)
		{
			ObjectRef obj;
			obj.refrenceID = pStudent.id;
			this->students.push_back(obj);
		}
		dynamic_array<ObjectRef> students;
		template<typename TransferFunction>
		void Transfer(TransferFunction& transfer)
		{
			super::Transfer(transfer);
			mTransfer(students);			 
		}
	};
	//还原数据关系时，严格还原了对象的创建顺序，所以链接的时候，不会出现空值
	std::string toYaml(ClassRoom& obj)
	{
		YamlWriter writer;
		writer.transfer("ClassRoom", obj);
		return writer.toString();
	}

	void _Main()
	{
		Student obj;
		obj.age = 20;
		obj.height = 180;
		obj.name = "xia";

		ClassRoom room;
		room.addStudent(obj);
		room.addStudent(obj);
		std::string result = toYaml(room);
		
		int i = 0;
	}

}