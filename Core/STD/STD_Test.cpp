#include "dynamic_array.h"
#include "vector_map.h"
#include "vector_set.h"
#include <string>
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

	TEST(DynamicArray)
	{ 
		// no allocation for empty array
		dynamic_array<int> array;
		CHECK_EQUAL(0, array.capacity());

		// push_back allocates
		int j = 1;
		array.push_back(j);
		CHECK_EQUAL(1, array.size());
		CHECK(array.capacity() > 0);

		// push_back(void)
		int& i = array.push_back();
		i = 666;
		CHECK_EQUAL(666, array.back());

		// clear frees memory?
		array.clear();
		CHECK_EQUAL(0, array.size());
		CHECK_EQUAL(0, array.capacity());

		// 3 item list
		j = 6;
		array.push_back(j);
		j = 7;
		array.push_back(j);
		j = 8;
		array.push_back(j);

		CHECK_EQUAL(3, array.size());

		// swapping
		dynamic_array<int>().swap(array);
		CHECK_EQUAL(0, array.capacity());
		CHECK_EQUAL(0, array.size());

		// reserve
		array.reserve(1024);
		CHECK_EQUAL(1024, array.capacity());
		CHECK_EQUAL(0, array.size());

		// copy assignment
		dynamic_array<int> array1;
		j = 888;
		array1.push_back(j);

		array = array1;

		CHECK_EQUAL(1, array.size());
		CHECK_EQUAL(888, array.back());
		CHECK_EQUAL(1, array1.size());
		CHECK_EQUAL(888, array1.back());
	}

	TEST(DynamicArrayMisc)
	{
		// no allocation for empty array
		dynamic_array<int> array;
		CHECK_EQUAL(0, array.capacity());
		CHECK(array.owns_data());
		CHECK(array.begin() == array.end());
		CHECK(array.empty());

		// push_back allocates
		int j = 1;
		array.push_back(j);
		CHECK_EQUAL(1, array.size());
		CHECK(array.capacity() > 0);

		// push_back(void)
		int& i = array.push_back();
		i = 666;
		CHECK_EQUAL(666, array.back());

		// clear frees memory?
		array.clear();
		CHECK_EQUAL(0, array.size());
		CHECK_EQUAL(0, array.capacity());

		// 3 item list
		array.push_back(6);
		array.push_back(7);
		array.push_back(8);

		CHECK_EQUAL(3, array.size());

		// swapping
		dynamic_array<int>().swap(array);
		CHECK_EQUAL(0, array.capacity());
		CHECK_EQUAL(0, array.size());

		// reserve
		array.reserve(1024);
		CHECK_EQUAL(1024, array.capacity());
		CHECK_EQUAL(0, array.size());

		// copy assignment
		dynamic_array<int> array1;
		j = 888;
		array1.push_back(j);

		array = array1;

		CHECK_EQUAL(1, array.size());
		CHECK_EQUAL(888, array.back());
		CHECK_EQUAL(1, array1.size());
		CHECK_EQUAL(888, array1.back());
	}


	TEST(DynamicArrayErase)
	{
		dynamic_array<int> arr;
		arr.push_back(1);
		arr.push_back(2);
		arr.push_back(3);
		arr.push_back(4);
		arr.push_back(5);
		dynamic_array<int>::iterator it;

		// erase first elem
		it = arr.erase(arr.begin());
		CHECK_EQUAL(2, *it);
		CHECK_EQUAL(4, arr.size());
		CHECK_EQUAL(2, arr[0]);
		CHECK_EQUAL(3, arr[1]);
		CHECK_EQUAL(4, arr[2]);
		CHECK_EQUAL(5, arr[3]);

		// erase 2nd to last elem
		it = arr.erase(arr.end() - 2);
		CHECK_EQUAL(5, *it);
		CHECK_EQUAL(3, arr.size());
		CHECK_EQUAL(2, arr[0]);
		CHECK_EQUAL(3, arr[1]);
		CHECK_EQUAL(5, arr[2]);

		// erase last elem
		it = arr.erase(arr.end() - 1);
		CHECK_EQUAL(arr.end(), it);
		CHECK_EQUAL(2, arr.size());
		CHECK_EQUAL(2, arr[0]);
		CHECK_EQUAL(3, arr[1]);
	}


	TEST(DynamicArrayEraseRange)
	{
		dynamic_array<int> vs;
		vs.resize_uninitialized(5);

		vs[0] = 0;
		vs[1] = 1;
		vs[2] = 2;
		vs[3] = 3;
		vs[4] = 4;

		vs.erase(vs.begin() + 1, vs.begin() + 4);
		CHECK_EQUAL(2, vs.size());
		CHECK_EQUAL(5, vs.capacity());
		CHECK_EQUAL(0, vs[0]);
		CHECK_EQUAL(4, vs[1]);
	}

	static void VerifyConsecutiveIntArray(dynamic_array<int>& vs, int size, int capacity)
	{
		CHECK_EQUAL(capacity, vs.capacity());
		CHECK_EQUAL(size, vs.size());
		for (size_t i = 0; i < vs.size(); i++)
			CHECK_EQUAL(i, vs[i]);
	}

	TEST(DynamicArrayInsertOnEmpty)
	{
		dynamic_array<int> vs;
		int vals[] = { 0, 1 };

		vs.insert(vs.begin(), vals, vals + ARRAY_SIZE(vals));

		VerifyConsecutiveIntArray(vs, 2, 2);
	}


	TEST(DynamicArrayInsert)
	{
		dynamic_array<int> vs;
		vs.resize_uninitialized(5);

		vs[0] = 0;
		vs[1] = 1;
		vs[2] = 4;
		vs[3] = 5;
		vs[4] = 6;

		int vals[] = { 2, 3 };

		// inser two values
		vs.insert(vs.begin() + 2, vals, vals + ARRAY_SIZE(vals));
		VerifyConsecutiveIntArray(vs, 7, 7);

		// empty insert
		vs.insert(vs.begin() + 2, vals, vals);

		VerifyConsecutiveIntArray(vs, 7, 7);
	}

	TEST(DynamicArrayResize)
	{
		dynamic_array<int> vs;
		vs.resize_initialized(3, 2);
		CHECK_EQUAL(3, vs.capacity());
		CHECK_EQUAL(3, vs.size());
		CHECK_EQUAL(2, vs[0]);
		CHECK_EQUAL(2, vs[1]);
		CHECK_EQUAL(2, vs[2]);

		vs.resize_initialized(6, 3);
		CHECK_EQUAL(6, vs.capacity());
		CHECK_EQUAL(6, vs.size());
		CHECK_EQUAL(2, vs[0]);
		CHECK_EQUAL(2, vs[1]);
		CHECK_EQUAL(2, vs[2]);
		CHECK_EQUAL(3, vs[3]);
		CHECK_EQUAL(3, vs[4]);
		CHECK_EQUAL(3, vs[5]);

		vs.resize_initialized(5, 3);
		CHECK_EQUAL(6, vs.capacity());
		CHECK_EQUAL(5, vs.size());
		CHECK_EQUAL(2, vs[0]);
		CHECK_EQUAL(2, vs[1]);
		CHECK_EQUAL(2, vs[2]);
		CHECK_EQUAL(3, vs[3]);
		CHECK_EQUAL(3, vs[4]);

		vs.resize_initialized(2, 3);
		CHECK_EQUAL(6, vs.capacity());
		CHECK_EQUAL(2, vs.size());
		CHECK_EQUAL(2, vs[0]);
		CHECK_EQUAL(2, vs[1]);
	}

	TEST(Test_vector_map)
	{
		struct Student
		{
			int age;  
		};
		vector_map<int, Student> id_name;
		id_name[0].age = 20; 
		id_name[1].age = 0; 
		CHECK_EQUAL(20, id_name[0].age);
		CHECK_EQUAL(2, id_name.size());
	
		size_t p1 = (size_t)&id_name[0];
		size_t p2 = (size_t)&id_name[1];
		size_t t1 = sizeof(vector_map<int, Student>::value_type);
		size_t t2 = ((p2- p1));
		CHECK(t1 == t2);
	}

	TEST(Test_vector_set)
	{
		vector_set<int> ids;
		ids.insert(9);
		ids.insert(0);
		ids.insert(7);
		vector_set<int>::iterator it = ids.begin();
		CHECK_EQUAL(0, *it);
		CHECK_EQUAL(7, *(it+1));
		CHECK_EQUAL(9, *(it+2));
	}

	 
}