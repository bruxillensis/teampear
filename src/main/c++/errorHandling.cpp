#include "errorHandling.h"
#include <string>
#include <exception>

using namespace std;


	string errorHandling::checkDate(string cellValue){if(cellValue == "") return ""; else return cellValue };
	bool errorHandling::checkEmpty(string cellValue){if(cellValue == "") return false; else return true;};
	bool errorHandling::checkValid(string cellValue){if(cellValue == "")return false; else return true;};
	int errorHandling::parseStoI(string cellValue){if(cellValue == "") return 0; else return 1;};
	float errorHandling::parseStoF(string cellValue){if(cellValue == "")return 0; else return 1;};
	int errorHandling::checkIfPublished(string cellValue){if(cellValue == "")return 0; else return 1;};	
