#pragma once
#include <string>
#include <exception>

using namespace std;

class errorHandling {
private:
	exception e;
public:
	static string checkDate(string cellValue);
	static bool checkEmpty(string cellValue);
	static bool checkValid(string cellValue);
	static int parseStoI(string cellValue);
	static float parseStoF(string cellValue);
	static int checkIfPublished(string cellValue);	

	//All error checking methods should be implemented in here.
	//All should be static implementations.
	//Output should be boolean or corrected value of cell.
};