#include <vector>
#include <string>
#include <map>

#include "professor.h"
using namespace std;

#pragma once
template <class T>
class professorMap {
private:
	map<T*>* professors;
public:
	//Chelsea
	professorMap();

	//Brett
	professorMap(string fileName);
	//Really important to clean up dynamic memory because of the size of possible files
	virtual ~professorMap();

	/*
	Should import csv by creating 'vitualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.
	*/
	//Chris
	void importCSV(string fileName);

	//Chelsea
	vector<string> getProfessorNameList();
	//Chelsea
	int getProfessorCount();
	//Chelsea
	const T* getProfessor(string professorName);
	//Brett
	const map<T*>::iterator getIterator();
	//Brett
	void addProfessor(T& newProfessor);
	//Brett
	void removeProfessor(string professorName);
};