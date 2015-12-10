#include "stdafx.h"
#include "CppUnitTest.h"
#include "errorHandling.h"
#include "vector"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTest
{
	TEST_CLASS(TesterrorHandling)
	{
	public:
		
		TEST_checkRow() //check for NULL case
		{
			// TODO: Your test code here
			//arrange
			vector<string> row = NULL;
			vector<string> columnHeaders = NULL;
			vector<string> mandatoryValues = NULL;
			//act
			errorHandling test = new errorHandling();
			bool actualValue = test.checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues);

			//assert
			Assert::AreEqual(false, actualValue, L"message", LINE_INFO());

		}

		TEST_checkRow2() //check fort true case
		{
			// TODO: Your test code here
			//arrange
			vector<string> row = new vector<string>;
			vector<string> columnHeaders = new vector<string>;
			vector<string> mandatoryValues = new vector<string>;
			//act
			errorHandling test = new errorHandling();
			bool actualValue = test.checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues);

			//assert
			Assert::AreEqual(true, actualValue, L"message", LINE_INFO());
			Assert::AreEqual(expectedValue, actualValue, L"message", LINE_INFO());

		}

		TEST_checkYear()//test for false
		{
			string date1 = NULL;
			string date2 = NULL;

			errorHandling test = new errorHandling();
			bool actualValue = test.checkYearRange(date1, date2);
			Assert::AreEqual(false, actualValue, L"message", LINE_INFO());

		}

		TEST_checkYear2()//test for true
		{
			//need to input valid date range when decided
			string date1 = "";
			string date2 = "";

			errorHandling test = new errorHandling();
			bool actualValue = test.checkYearRange(date1, date2);
			Assert::AreEqual(true, actualValue, L"message", LINE_INFO());

		}
	};
}