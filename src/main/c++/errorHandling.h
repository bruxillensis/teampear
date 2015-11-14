#pragma once
#include <string>
#include <exception>
#include <vector>

using namespace std;

class errorHandling {
private:
	exception e;
public:
	//Validate each row of data that the model passes through into professor objects
	static bool checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues);

	// Validate the filter of the date range
	static int checkYear(string date);
	static bool checkFilter(int date);
	static bool toBool(string boolValue);
	static float toFloat(string floatValue);
	static int toInt(string intValue);
	//All error checking methods should be implemented in here.
	//All should be static implementations.
	//Output should be boolean or corrected value of cell.
};