cmake_minimum_required (VERSION 3.1) 
 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)

my_add_library(Core
	Function/FunctionTest.cpp
	Function/Operator/Operator.cpp
	Memory/MemoryTest.cpp
	Memory/MemoryPool.cpp
	Memory/New.cpp
	STD/STD_Test.cpp
${CURRENT_HEADERS}
)
 
