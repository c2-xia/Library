cmake_minimum_required (VERSION 3.1) 
 
add_library(UnitTest++
	./Win32/TimeHelpers.cpp
	AssertException.cpp
	Checks.cpp
	CompositeTestReporter.cpp
	CurrentTest.cpp
	DeferredTestReporter.cpp
	DeferredTestResult.cpp
	MemoryOutStream.cpp
	ReportAssert.cpp
	RequiredCheckException.cpp
	RequiredCheckTestReporter.cpp
	Test.cpp
	TestDetails.cpp
	TestList.cpp
	TestReporter.cpp
	TestReporterStdout.cpp
	TestResults.cpp
	TestRunner.cpp
	ThrowingTestReporter.cpp
	TimeConstraint.cpp
	XmlTestReporter.cpp
)