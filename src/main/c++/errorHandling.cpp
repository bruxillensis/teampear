#include "stdafx.h"
#include "errorHandling.h"
#include "modelExceptions.h"
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

//Validate each row of data that the model passes through into professor objects
bool errorHandling::checkRow(vector<string> row, vector<string> columnHeaders, vector<string> mandatoryValues){
	vector<int> mandatoryNdx; // this will hold the indices of the mandatory column

	for (string &mandVal : mandatoryValues) // loop through each of the mandatory column names
	{
		//Search through the column headers for the mandatory ones
		auto found = find(columnHeaders.begin(), columnHeaders.end(), mandVal);
		if (found == columnHeaders.end()){
			throw new manditoryHeaderNotFoundException();
		}else{
			//Set the proper index by subtracting it from the beginning
			auto index = distance(columnHeaders.begin(), found);
			//Store the mandatory index
			mandatoryNdx.push_back(index);
		}
	}
	
	//Check the mandatory indices of the actual row
	for (int &checkNdx : mandatoryNdx){
		if (row[checkNdx] == ""){
			//There is an empty mandatory cell!
			throw new emptyManditoryCellException();
		}
	}
	//There are no empty mandatory cells
	return true; 
}

// Validate the filter of the date range
int errorHandling::checkYear(string date){
	//Get year from date string
	istringstream ss(date);
	string syear;
	getline(ss, syear, '/');
	
	//Reset stringstream and convert year to integer
	ss.str(syear);
	ss.clear();
	int nyear;
	ss >> nyear;

	//Type cast to float to check if it is a year and return
	if ((float)nyear / 1000 < 1)
		throw new yearNotSpecifiedException();
	else
		return nyear;
}
