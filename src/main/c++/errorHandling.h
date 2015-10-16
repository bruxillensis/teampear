#pragma once
#include <string>
#include <exception>

using namespace std;

class errorHandling {
private:
	exception e;
public:
	//check if a cell has valid date
	static string checkDate(string cellValue);
	//check if a cell is empty
	static bool checkEmpty(string cellValue);
	//Check if a cell has valid data
	static bool checkValid(string cellValue);
	//Parse a string to integer
	static int parseStoI(string cellValue);
	//Parse string to float
	static float parseStoF(string cellValue);

	//All error checking methods should be implemented in here.
	//All should be static implementations.
	//Output should be boolean or corrected value of cell.
};