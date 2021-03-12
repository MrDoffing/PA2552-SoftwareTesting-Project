#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PA2552SoftwareTestingProject
{
	TEST_CLASS(PA2552SoftwareTestingProject)
	{
	public:
		
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("In Method Initialize");
		}
		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("In Method Cleanup");
		}
		TEST_METHOD(TestMethod_Add)
		{
			Logger::WriteMessage("InMethod - Add");
			Assert::IsTrue(Calculator::add(3, 4) == 7);
			Assert::IsTrue(Calculator::add(-2, -1) == -3);
		}
		TEST_METHOD(TestMethod_Sub)
		{
			Logger::WriteMessage("InMethod - Sub");
			Assert::IsTrue(Calculator::sub(3, 4) == -1);
			Assert::IsTrue(Calculator::sub(5, -1) == 6);
		}
		TEST_METHOD(TestMethod_Mul)
		{
			Logger::WriteMessage("InMethod - Mul");
			Assert::IsTrue(Calculator::mul(4, 5) == 20);
		}
	};
}
