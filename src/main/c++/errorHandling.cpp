#include "stdafx.h"
#include "errorHandling.h"
#include "modelExceptions.h"
#include "boost/date_time/gregorian/gregorian.hpp"
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
			throw manditoryHeaderNotFoundException();
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
			throw emptyManditoryCellException();
		}
	}
	//There are no empty mandatory cells
	return true; 
}

// Validate the filter of the date range
boost::gregorian::date errorHandling::checkYear(string date){
	//Get date values from date string
	istringstream ss(date);
	string syear, smonth, sday;
	getline(ss, syear, '/');
	getline(ss, smonth, '/');
	getline(ss, sday);
	//Reset stringstream and convert date to int values
	int nyear, nmonth, nday;
	if (syear != ""){
		ss.str(syear);
		ss.clear();
		ss >> nyear;
	}
	else{ nyear = 1900; }
	if (smonth != ""){
		ss.str(smonth);
		ss.clear();
		ss >> nmonth;
	}
	else{ nmonth = 1; }
	if (sday != ""){
		ss.str(sday);
		ss.clear();
		ss >> nday;
	}
	else{ nday = 1; }
	try{
		return boost::gregorian::date(nyear, nmonth, nday);
	}
	catch (...){
		throw new invalidDateException();
	}
}

//Implement
bool errorHandling::checkFilter(int date){
	return true;
}

bool errorHandling::toBool(string boolValue){
	if (boolValue.compare("TRUE"))
		return true;
	if (boolValue.compare("FALSE"))
		return false;
	throw new failedTypeChangeException();
}

float errorHandling::toFloat(string floatValue){
	vector<char> s;
	//Convert string to vector to iterate through
	for (char& i : vector<char>(floatValue.begin(), floatValue.end())){
		//If value is a number or period add to output string vector
		if (((i<57) && (i>48)) || (i == 46))
			s.push_back(i);
	}
	try{
		//Convert to string and attempt to convert to float
		return std::stof(string(s.begin(), s.end()));
	}
	catch (const std::invalid_argument& ia){
		//If no meaningful output throw exception
		throw new failedTypeChangeException();
	}
}

int errorHandling::toInt(string intValue){
	vector<char> s;
	//Convert string to vector to iterate through
	for (char& i : vector<char>(intValue.begin(), intValue.end())){
		//If value is a number or period add to output string vector
		if (((i<57) && (i>48)) || (i == 46))
			s.push_back(i);
	}
	try{
		//Convert to string and attempt to convert to int
		return std::stoi(string(s.begin(), s.end()));
	}
	catch (const std::invalid_argument& ia){
		//If no meaningful output throw exception
		throw new failedTypeChangeException();
	}
}