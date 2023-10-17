#include "pch.h"
#include "CppUnitTest.h"
#include "../Vector/Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::vector;

namespace VectorTest
{
	TEST_CLASS(VectorTest)
	{
	public:

		TEST_METHOD(IndexOperator_IncorrectIndex_ExeptionExpected)
		{

			Assert::ExpectException<std::out_of_range>([]()
				{auto x = Vector({ 12, 33,44,55,11 }); x[10]; });
		}

		TEST_METHOD(Pop_IncorrectIndex_ExeptionExpected)
		{

			Assert::ExpectException<std::out_of_range>([]()
				{auto x = Vector({ 12, 33,44,55,11 }); x.pop(10); });
		}

		TEST_METHOD(ToString_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Assert::IsTrue(vector_1.to_string() == "[ 12 33 44 55 11 ]");
		}

		TEST_METHOD(EqualityOperator_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Vector vector_2{ 12, 33,44,55,11 };
			Assert::IsTrue(vector_1 == vector_1);
		}

		TEST_METHOD(GetSize_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Assert::IsTrue(vector_1.get_size() == 5);
		}

		TEST_METHOD(Append_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			vector_1.append(12);
			Vector expected_vector{ 12,33,44,55,11,12 };
			Assert::IsTrue(vector_1 == expected_vector);
		}

		TEST_METHOD(Pop_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			vector_1.pop(1);
			Vector expected_vector{ 12,44,55,11 };
			Assert::IsTrue(vector_1 == expected_vector);
		}

		TEST_METHOD(Find_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Assert::IsTrue(vector_1.find(33) == 1);
		}

		TEST_METHOD(IsEmpty_ValidData_Success)
		{
			Vector vector_1{};
			Assert::IsTrue(vector_1.is_empty());
		}

		TEST_METHOD(OutputOperator_ValidData_Success)
		{
			std::stringstream sstring;
			Vector vector = Vector({ 10,11,12,13 });
			sstring << vector;
			Assert::AreEqual(sstring.str(), vector.to_string());
		}

		TEST_METHOD(CopyOperator_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Vector vector_2{ 33, 22 ,44, 55 };
			vector_1 = vector_2;
			Assert::IsTrue(vector_1 == vector_2);
		}

		TEST_METHOD(MoveOperator_ValidData_Success)
		{
			Vector vector_1{ 12, 33,44,55,11 };
			Vector vector_2{ 33, 22 ,44, 55 };
			vector_1 = std::move(vector_2);
			Vector expected_vector{ 33, 22 ,44, 55 };
			Assert::IsTrue(vector_1 == expected_vector);
		}

	};
}
