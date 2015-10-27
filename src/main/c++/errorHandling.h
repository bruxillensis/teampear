#pragma once
#include <string>
#include <exception>
#include <vector>

using namespace std;

class errorHandling {
private:
	exception e;
public:
	static string checkDate(string cellValue); // should this change the date to JUST year?
	static bool checkEmpty(string cellValue);
	static bool checkValid(string cellValue);
	static int parseStoI(string cellValue);
	static float parseStoF(string cellValue);
	static int checkIfPublished(string cellValue);
	//Henry
	//Validate each row of data that the model passes through into professor objects
	static bool checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues);

	//Henry
	// Validate the filter of the date range
	static int checkYear(string date);

	//All error checking methods should be implemented in here.
	//All should be static implementations.
	//Output should be boolean or corrected value of cell.
};