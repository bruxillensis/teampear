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

	void importCSV(string fileName);
	void exportCSV(string fileName);

	//Returns list of professor names in the csv
	vector<string> getListofProfessorNames();

	string getCell(string professorName, int rowID, int columnID);
	int getNumberofRows(string professorName);
	int getRowPosition(string professorName);
	int getColumnPosition(string columnName);
};