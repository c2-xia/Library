#include "../UnitTest++/UnitTestPP.h"

#include "defines.h"
#include "Object/_Vector3.h"
#include "Object/_quaternionf.h"
#include "Math/Lerp.h"
#include "Math/Floor.h"
#include "Math/Repeat.h"
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
    
	TEST(FloorTest)
	{ 
		CHECK_EQUAL(Floorf(2.3f), 2);
		CHECK_EQUAL(Floorf(0.6f), 0);
		CHECK_EQUAL(Floorf(-2.3f), -3);

		CHECK_EQUAL(Floord(2.3), 2);
		CHECK_EQUAL(Floord(0.6), 0);
		CHECK_EQUAL(Floord(-2.3), -3);
	}

	TEST(RepeatTest)
	{
		float v = Repeatf(5.0f, 4.5f);
		CHECK_EQUAL(v, 0.5);
		double v2 = Repeatd(5.0, 4.5);
		CHECK_EQUAL(v2, 0.5);
	}

}