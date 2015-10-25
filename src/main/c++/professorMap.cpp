#include "stdafx.h"
#include "professorMap.h"
#include "errorHandling.h"
#include "createProfessor.h"
#include <iostream>
#include <map>
#include <type_traits>

using namespace std;

template <class T>
professorMap<T>::professorMap() {
    this->professors = new map<string, T*>();
}

template <class T>
professorMap<T>::professorMap(string fileName){
	this->professors = new map<string, T*>();
	this->importCSV(fileName);
}

template <class T>
professorMap<T>::~professorMap(){
	for (map<string, T*>::iterator it = this->professors->begin(); it != this->professors->end(); ++it)
		delete (*it).second;
	delete professors;
}

/*
Should import csv by creating 'vitualization' of	
2D array (vector<vector<string>>) then
calling createProfessor() for each professor entry.
*/

template <class T>
void professorMap<T>::importCSV(string fileName) {
	//read CSV file into 2D array
	vector<vector<string>*> myCSV;
	vector<string>* valueLine;
	ifstream inFile(fileName);
	string temp;

	//make 2D vector 
	for (string line; getline(inFile, line); )
	{
		istringstream in(line);
		valueLine = new vector<string>();
		while (getline(in, temp, ','))
			valueLine->push_back(temp);

		myCSV.push_back(valueLine);
	}

	map<string, vector<vector<string>>>* orgCSV = new map<string, vector<vector<string>>>();
	for (int i = 0; i < myCSV.size(); i++) {
		if (!orgCSV->empty()){
			map<string, vector<vector<string>>>::iterator it = orgCSV->find(myCSV[i][0]);
			if ((*it).first == myCSV[i][0])
				(*it).second.push_back(myCSV[i]);
			else {
				vector<vector<string>> professorVector;
				professorVector.push_back(myCSV[0]);
				professorVector.push_back(myCSV[i]);
				orgCSV->insert(pair<string, vector<vector<string>>>(myCSV[i][0], professorVector));
			}
		}
		else {
			vector<vector<string>> professorVector;
			professorVector.push_back(myCSV[0]);
			professorVector.push_back(myCSV[i]);
			orgCSV->insert(pair<string, vector<vector<string>>>(myCSV[i][0], professorVector));
		}
	}

	for (map<string, vector<vector<string>>>::iterator it = orgCSV->begin(); it != orgCSV->end(); ++it) {
		T* professor = createNewProfessor((*it).second());
		this->professors->insert(pair<string, T*>(professor->getName(),professor));
	}
	for (int i = 0; i < myCSV.size(); i++)
		delete myCSV[i];
	delete orgCSV;
}

template <class T>
vector<string>* professorMap<T>::getProfessorNameList(){
    vector<string>* listOfProfs = new vector<string>;
	for (map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++it)
		listOfProfs->push_back(it->first);
    return listOfProfs;
}

template <class T>
int professorMap<T>::getProfessorCount() {    
    return this->professors->size();
}

template <class T>
const T* professorMap<T>::getProfessor(string professorName){
	std::map<string, T*>::iterator it = this->professors->find(professorName);
	if ((*it).first == professorName)
		return (*it).second;
	throw new professorNotFoundException();
}

template <class T>
typename std::map<string, T*>::iterator professorMap<T>::begin() { return this->professors->begin(); }

template <class T>
typename std::map<string, T*>::iterator professorMap<T>::end() { return this->professors->end(); }

template <class T>
void professorMap<T>::addProfessor(T& newProfessor) { this->professors->insert(newProfessor.getName(), newProfessor); }

template <class T>
void professorMap<T>::removeProfessor(string professorName){
	map<string, T*>::iterator it = this->professors->find(professorName);
	if ((*it).first == professorName)
		this->professors->erase(it);
	else
		throw new professorNotFoundException();
}