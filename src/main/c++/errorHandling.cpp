#include "stdafx.h"
#include "errorHandling.h"

using namespace std;
// rather than checkDate, should we convertDate to just year in order to standardize it?
string errorHandling::checkDate(string cellValue){if(cellValue == "") return ""; else return cellValue; };
bool errorHandling::checkEmpty(string cellValue){if(cellValue == "") return false; else return true;};
bool errorHandling::checkValid(string cellValue){if(cellValue == "")return false; else return true;};
int errorHandling::parseStoI(string cellValue){if(cellValue == "") return 0; else return 1;};
float errorHandling::parseStoF(string cellValue){if(cellValue == "")return 0; else return 1;};
int errorHandling::checkIfPublished(string cellValue){if(cellValue == "")return 0; else return 1;};	
//Henry
//Validate each row of data that the model passes through into professor objects
bool errorHandling::checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues){
	vector<int> mandatoryNdx; // this will hold the indices of the mandatory column

	for (string &mandVal : mandatoryValues) // loop through each of the mandatory column names
	{
		auto temp = std::find(columnHeaders.begin(), columnHeaders.end(), mandVal); // search through the column headers for the mandatory ones
		if (temp == columnHeaders.end())
		{
			cout << "Not Found In columnHeaders";
		}else
		{
			auto index = std::distance(columnHeaders.begin(), temp); // Get the proper index by subtracting it from the beginning
			mandatoryNdx.push_back(index); // store the mandatory index
		}
	}

	for (int &checkNdx : mandatoryNdx) // Check the mandatory indices of the actual row 
	{
		if (row[checkNdx] == "")
		{
			//there is an empty mandatory cell!
			return false;
		}
	}
	//there are no empty mandatory cells
	return true; 
}

//Henry
// Validate the filter of the date range
bool errorHandling::checkYearRange(string date1, string date2){
	int year1 = stoi(date1);
	int year2 = stoi(date2);

	// Determine the current year
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int currentYear = aTime->tm_year + 1900; // Year is # years since 1900

	// Invalid if: 
	// - year1 or year2 are above the current year
	// - year1 is past year 2
	if ((year1 > currentYear) || (year2 > currentYear) || year1 > year2){
		return false;
	}else
	{
		return true;
	}
}
