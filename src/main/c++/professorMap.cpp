#include "stdafx.h"
#include "professorMap.h"
#include "errorHandling.h"
#include "createProfessor.h"
#include <iostream>

using namespace std;

//Chelsea
template <class T>
professorMap<T>::professorMap() {
    this->professors = new map<string, T*>();
}

template <class T>
professorMap<T>::professorMap(string fileName){
	this->professors = new map<string, T*>();
	this->importCSV(fileName);
}

//Really important to clean up dynamic memory because of the size of possible files
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
//Chris
template <class T>
void professorMap<T>::importCSV(string fileName){
	//read CSV file into 2D array
	vector<vector<string>> myCSV;
	vector<string>* valueLine;
	ifstream inFile("database.txt");
	string temp;

	//make 2D vector 
	for (string line; getline(inFile, line); )
	{
		istringstream in(line);
		valueLine = new vector<string>();
		while (getline(in, temp, ','))
		{
			valueLine->push_back(temp);
		}

		myCSV.push_back(*valueLine);
	}

	//check every row
	for (size_t i = 1; i < myCSV.size(); i++) {
		if (!checkRow(myCSV[i], myCSV[0], ? ? ? ? ? )) {
			myCSV.erase(myCSV.begin() + i);
			i--;
		}
	}

	//call createProfessor for each line
	//createNewProfessor(string professorName, vector<vector<string>>& csv, int begRow);
	for (size_t i = 0; i < myCSV.size(); i++) {
		createNewProfessor(myCSV[i][4],myCSV,int(i));
	}

	//data check
	for (size_t i = 0; i < myCSV.size(); i++) {
		for (size_t j = 0; j < myCSV[i].size(); j++) {
			cout << i << " " << j << " " << myCSV[i][j] << '\n';
		}
	}
	cin >> temp;
}



//Chelsea
template <class T>
vector<string> professorMap<T>::getProfessorNameList(){

    vector<string> listOfProfs;
    
//iterate through the map
    for(map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++it){
        
        listOfProfs.push_back(it->first);
    }

    return listOfProfs;
}
//Chelsea
template <class T>
int professorMap<T>::getProfessorCount() {

    int counter = 0;
    
    //iterate through the map and count the entries (number of profs)
    for(map<string, T*>::iterator it = professors.being(); it != professors.end(); ++it){
        
        counter++;
    }
    
    return counter;

}
//Chelsea
template <class T>
const T* professorMap<T>::getProfessor(string professorName){

    //iterate through the map and compare the professor name
    for(map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++i){
        
        if (it->first == professorName) {
            return it->second; //return the professor when name matches
        }
    }
    
    return NULL; //return null if the professor's name is not found in map
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