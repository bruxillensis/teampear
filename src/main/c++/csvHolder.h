#include <vector>
#include <string>
#include "professor.h"
using namespace std;

#pragma once
class csvHolder {
private:
	vector<vector<string>> excelFile;
public:
	csvHolder();
	csvHolder(string fileName);
	virtual ~csvHolder();

	//Imports CSV file from file name
	void importCSV(string fileName);
	//Exports CSV file to file name
	void exportCSV(string fileName);

	//Returns list of professor names in the csv
	vector<string> getListofProfessorNames();

	//Returns value of a cell for a professor at rowID and columnID
	string getValue(string professorName, int rowID, int columnID);
	//Returns the number of rows associated to a professor
	string getNumberofRows(string professorName);
};