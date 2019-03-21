#include "dynamic_array.h"

#include "../UnitTest++/UnitTestPP.h"


using namespace UnitTest;

namespace {

	TEST(Check_dynamic_array)
	{
		struct Strudent {
			int x;
			int y;
			int sex;
		};
		dynamic_array<Strudent> stdudents;
		Strudent a;
		a.x = 99;
		stdudents.push_back(a);
		CHECK_EQUAL(a.x, stdudents[0].x);
		CHECK(&a != &stdudents[0]);

		stdudents.push_back(a);
		stdudents.push_back(a);
		CHECK_EQUAL(4, stdudents.capacity());
		stdudents.push_back(a);
		stdudents.push_back(a);
		CHECK_EQUAL(8, stdudents.capacity());
	}


}