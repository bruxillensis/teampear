#include "stdafx.h"
#include "professorMap.h"
#include "errorHandling.h"
#include "createProfessor.h"
#include <iostream>
#include <map>

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
void professorMap<T>::importCSV(string fileName) {
	//read CSV file into 2D array
	vector<vector<string>> myCSV;
	vector<string>* valueLine;
	ifstream inFile("database.txt");
	string temp;
	T* tempT;


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

	//check what type of professor
	vector<string>* manFields;
	if (T == pubProfessor) {
		manFields = {"Member Name", "Primary Domain", "Publication Status", "Type", "Status Date", "Role", "Journal Name | Published In | Book Title | etc.", "Author(s)", "Title"};

	}
	else if (T == presProfessor) {
		//date, member name, type, role
	}
	else if (T == teacProfessor) {
		//start date, member name, program, hours, number of students
	}
	else if (T == granProfessor) {
		//start date, member name, funding type, peer reviewed OR industry sponsored, status, role, amount, title
	}

	//calls checkrow function to check each row dependent on type of professor
	for (size_t i = 1; i < myCSV.size(); i++) {
		if (!checkRow(myCSV[i], myCSV[0], manFields)) {
			myCSV.erase(myCSV.begin() + i);
			i--;
		}
	}



	//hmmmmmmmmmmm, needs to be something here that combines all of a certain professor's rows



	//call createProfessor for each line
	//createNewProfessor(string professorName, vector<vector<string>>& csv, int begRow);
	for (size_t i = 0; i < myCSV.size(); i++) {
		tempT = createNewProfessor(myCSV[i][4],myCSV,int(i));
		professors.insert(pair<string, T*>(tempT->getName(),tempT));
	}

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