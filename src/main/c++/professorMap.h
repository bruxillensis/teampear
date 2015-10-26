#pragma once
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include "pubProfessor.h"

using namespace std;

#pragma once
template <class T>
class professorMap {
private:
	map<string, T*>* professors;
public:
	typedef typename map<string, T*>::iterator iterator;

	//Chelsea
	professorMap();
	professorMap(string fileName);
	//Really important to clean up dynamic memory because of the size of possible files
	virtual ~professorMap();

	/*
	Should import csv by creating 'virtualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.
	*/
	void importCSV(string fileName);

	vector<string>* getProfessorNameList();
	int getProfessorCount();
	const T* getProfessor(string professorName);

	typename map<string, T*>::iterator begin();
	typename map<string, T*>::iterator end();

	void addProfessor(T& newProfessor);
	void removeProfessor(string professorName);
	vector<pair<string,vector<pair<string,int> > > > callMe();
};
