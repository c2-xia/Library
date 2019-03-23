cmake_minimum_required (VERSION 3.1) 
 
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)

add_library(Math
	./Function/FunctionTest.cpp
	./Function/operator.cpp
	./Memory/MemoryTest.cpp
	./Memory/MemoryPool.cpp
	./Memory/New.cpp
	./Std/STD_Test.cpp
${CURRENT_HEADERS}
)
