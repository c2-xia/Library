#include "../UnitTest++/UnitTestPP.h"

#include "defines.h"
#include "Object/_Vector3.h"
#include "operator.h"
#include "Lerp.h"

using namespace UnitTest;

namespace {
 
	TEST(LerpTest)
	{
		_Vector3 v;
		v.x = 1;
		v.y = 1;
		v.z = 1;
		_Vector3 v_zeor;
		real t = 0.3f;
		_Vector3 v2 = Lerp( v_zeor, v, t);
		CHECK_EQUAL(v2.x , t);
		CHECK_EQUAL(v2.y , t);
		CHECK_EQUAL(v2.z , t);
		real v_real = 1;
		real v_real2 = Lerp(0, v_real, t);
		CHECK_EQUAL(v_real2, t);
	}
    

}