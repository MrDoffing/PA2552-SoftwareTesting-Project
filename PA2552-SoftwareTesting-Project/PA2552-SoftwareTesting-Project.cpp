#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PA2552SoftwareTestingProject
{
	TEST_CLASS(PA2552SoftwareTestingProject)
	{
	public:
		
		TEST_METHOD(TestMethod_Add)
		{
			Assert::IsTrue(Calculator::add(3, 4) == 7);
			Assert::IsTrue(Calculator::add(-2, -1) == -3);
		}
		TEST_METHOD(TestMethod_Sub)
		{
			Assert::IsTrue(Calculator::sub(3, 4) == -1);
			Assert::IsTrue(Calculator::sub(5, -1) == 6);
		}
		TEST_METHOD(TestMethod_Mul)
		{
			Assert::IsTrue(Calculator::mul(4, 5) == 20);
		}
	};
}
