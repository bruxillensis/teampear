#pragma once
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include "pubProfessor.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "createProfessor.h"
#include "csv_parser.hpp"



using namespace std;

#pragma once
template <class T>
class professorMap {
private:
	map<string, T*>* professors;
public:
	typedef typename map<string, T*>::iterator iterator;

	professorMap() {
		this->professors = new map<string, T*>();
	}
	professorMap(string fileName) {
		this->professors = new map<string, T*>();
		this->importCSV(fileName);
	}
	//Really important to clean up dynamic memory because of the size of possible files
	virtual ~professorMap() {
		for (map<string, T*>::iterator it = this->professors->begin(); it != this->professors->end(); ++it)
			delete (*it).second;
		delete professors;
	}

	/*
	Should import csv by creating 'virtualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.
	*/
	void importCSV(string fileName) {
		//read CSV file into 2D array
		
		vector<vector<string>*> myCSV;
		vector<string>* valueLine;
		CSV_Parser csv_parser;
		string line;
		bool status;

		// Open the test case CSV file
		ifstream test_file(fileName);
		if (test_file.is_open())
		{
			//read every line in the file
			while (getline(test_file, line))
			{
				valueLine = new vector<string>();
				//cout << "CSV line - " << line << "\n";
				status = csv_parser.parse_line(line, *valueLine);
				if (status)
				{
					myCSV.push_back(valueLine);
				}
				else
				{
					cout << "Error encountered while parsing the input line\n";
				}
			}
		}
		/*cout << myCSV.size() << "\n";
		cout << myCSV[0]->size() << "\n";
		cout << myCSV[1]->size() << "\n";
		cout << myCSV[2]->size() << "\n";
		cin >> line;

		for (size_t i = 0; i < myCSV.size(); i++) {
			for (size_t j = 0; j < myCSV[i]->size(); j++) {
				cout << i << " " << j << ": " << myCSV[i]->at(j);
				cout << '\n';
			}
		}

		cin >> line;
		*/

		map<string, vector<vector<string> > >* orgCSV = new map<string, vector<vector<string> > >();
		for (size_t i = 1; i < myCSV.size(); i++) {
			cout << "here\n";
			if (!orgCSV->empty()) {
				map<string, vector<vector<string> > >::iterator it = orgCSV->find((*myCSV[i])[4]);
				if (it != orgCSV->end()) {
					(*it).second.push_back(*myCSV[i]);
				}
				else {
					vector<vector<string> > professorVector;
					professorVector.push_back(*myCSV[0]);
					professorVector.push_back(*myCSV[i]);
					orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[4], professorVector));
				}
			}
			else {
				vector<vector<string> > professorVector;
				professorVector.push_back(*myCSV[0]);
				professorVector.push_back(*myCSV[i]);
				orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[4], professorVector));
			}
		}

		for (map<string, vector<vector<string> > >::iterator it = orgCSV->begin(); it != orgCSV->end(); ++it) {
			T* professor = createProfessor<pubProfessor>::createNewProfessor((*it).second);
			this->professors->insert(pair<string, T*>(professor->getName(), professor));
			//cout << "professors: " << professors->size();
		}
		for (size_t i = 0; i < myCSV.size(); i++)
			delete myCSV[i];
		delete orgCSV;
		int counter = 0;

		for (map<string, T*>::iterator it = professors->begin(); it != professors->end(); it++)
		{
			counter++;
			cout << counter << " " << it->first << "\n";
		}

	}

	vector<string>* getProfessorNameList() {
		vector<string>* listOfProfs = new vector<string>;
		for (map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++it)
			listOfProfs->push_back(it->first);
		return listOfProfs;
	}

	int getProfessorCount() {
		return this->professors->size();
	}
	const T* getProfessor(string professorName) {
		std::map<string, T*>::iterator it = this->professors->find(professorName);
		if ((*it).first == professorName)
			return (*it).second;
		throw new professorNotFoundException();
	}

	typename map<string, T*>::iterator begin() { return this->professors->begin(); }
	typename map<string, T*>::iterator end() { return this->professors->end(); }

	void addProfessor(T& newProfessor) { this->professors->insert(newProfessor.getName(), newProfessor); }

	void removeProfessor(string professorName) {
		map<string, T*>::iterator it = this->professors->find(professorName);
		if ((*it).first == professorName)
			this->professors->erase(it);
		else
			throw new professorNotFoundException();
	}
	/*
		Returns organized statistics of a professor type.
		In the professor classes there is a static list of string names to organize many professors by.
		This function gets that list, gets the statistics of each professor and returns the statistics
		of the professors organized by the static list

		ex. Static list in pubProfessor = "Book Chapters", "Books", "Books Edited", "Case Reports", etc.
		returns Book Chapters
					Prof A, Number of pubs of type Book Chapters
					Prof B, Number of pubs of type Book Chapters
				Books
					Prof A, Number of pubs of type Book

				etc.
	*/
	vector<pair<string,vector<pair<string,int> > > > callMe(int begYear, int endYear) {
		//Define return vector
        vector<pair<string, vector<pair<string, int> > > > returnVector;

		//Iterate through professors
        for (typename map<string, T*>::iterator it = professors->begin(); it != professors->end(); ++it) {
			//Get statistics of professor
			vector<pair<string, int>*>* profStats = it->second->getStatistics();
			//Iterate through statistics
			for (int i = 0; i < profStats->size(); i++){
				//Search through return vector, if type is found add this prof to it and break
				for (int j = 0; j < returnVector.size(); j++){
					if (profStats->at(i)->first == returnVector[j].first)
						returnVector[j].second.push_back(pair<string, int>(it->first, profStats->at(i)->second));
					break;
				}
				//If type is not found add the new type to the back of the vector and add this prof to it
				returnVector.push_back(pair<string, vector<pair<string, int>>>(profStats->at(i)->first, vector<pair<string, int>>()));
				returnVector[returnVector.size()-1].second.push_back(pair<string, int>(it->first, profStats->at(i)->second));
			}
			//Clean up
			for (int i = 0; i < profStats->size(); i++)
				delete profStats->at(i);
			delete profStats;
		}
        return returnVector;
	}
};
