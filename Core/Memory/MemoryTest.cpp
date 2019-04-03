#include "../../UnitTest++/UnitTestPP.h"
 

#include <cstring>

using namespace UnitTest;

#if _DEBUG
class New_G_Values
{
public:
	int value;
	static   New_G_Values* Instance;
}; 
#endif
namespace {

   TEST(CheckMyNewOperatorTest)
   {
	   struct Strudent {
		   int x;
		   int y;
		   int sex;
	   };
	   New_G_Values::Instance->value = 0;
	   Strudent* ps = new Strudent();
	   CHECK_EQUAL(20195, New_G_Values::Instance->value);
	   delete ps;
	   CHECK_EQUAL(20197, New_G_Values::Instance->value);
	   New_G_Values::Instance->value = 0;
	   Strudent* pss = new Strudent[2];
	   CHECK_EQUAL(20196, New_G_Values::Instance->value);
	   delete[] pss;
	   CHECK_EQUAL(20198, New_G_Values::Instance->value);
   }

}