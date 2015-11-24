#pragma once
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include "createProfessor.h"
#include "csv_parser.hpp"

using namespace std;

#pragma once
class professorMap {
private:
	map<string, professor*>* professors;
public:
	enum profType { Publication, Presentation, GrantClinical, Teaching };
	professorMap() {
		this->professors = new map<string, professor*>();
	}
	professorMap(string fileName, profType type) {
		this->professors = new map<string, professor*>();
		this->importCSV(fileName, type);
	}
	virtual ~professorMap() {
		for (auto& it : *professors)
			delete it.second;
		delete professors;
	}

	/*
	Should import csv by creating 'virtualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.
	*/
	void importCSV(string fileName, profType type) {
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

		map<string, vector<vector<string> > >* orgCSV = new map<string, vector<vector<string> > >();
		vector<string> mName;
		mName.push_back("Member Name");
		vector<int> indexMemberName = createProfessor::findHeaders(mName, *(myCSV.at(0)));

		for (size_t i = 1; i < myCSV.size(); i++) {
			if (!orgCSV->empty()) {
				if (myCSV[i]->at(indexMemberName.front()) == "")
					continue;
				map<string, vector<vector<string> > >::iterator it = orgCSV->find(myCSV[i]->at(indexMemberName.front()));
				if (it != orgCSV->end()) {
					it->second.push_back(*myCSV[i]);
				}
				else {
					vector<vector<string> > professorVector;
					professorVector.push_back(*myCSV[0]);
					professorVector.push_back(*myCSV[i]);
					orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[indexMemberName.front()], professorVector));
				}
			}
			else {
				vector<vector<string> > professorVector;
				professorVector.push_back(*myCSV[0]);
				professorVector.push_back(*myCSV[i]);
				orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[indexMemberName.front()], professorVector));
			}
		}

		for (map<string, vector<vector<string> > >::iterator it = orgCSV->begin(); it != orgCSV->end(); ++it) {
			professor* prof;
			switch (type){
			case Publication:
				prof = createProfessor::createNewPubProfessor(it->second);
				break;
			case Presentation:
				prof = createProfessor::createNewPresProfessor(it->second);
				break;
			case GrantClinical:
				prof = createProfessor::createNewGranProfessor(it->second);
				break;
			case Teaching:
				prof = createProfessor::createNewTeacProfessor(it->second);
				break;
			}
			this->professors->insert(pair<string, professor*>(prof->getName(), prof));
		}
		for (size_t i = 0; i < myCSV.size(); i++)
			delete myCSV[i];
		delete orgCSV;
	}

	bool empty(){ return this->professors->empty(); };

	vector<string>* getProfessorNameList() {
		vector<string>* listOfProfs = new vector<string>;
		for (map<string, professor*>::iterator it = this->professors->begin(); it != this->professors->end(); ++it)
			listOfProfs->push_back(it->first);
		return listOfProfs;
	}

	int getProfessorCount() {
		return this->professors->size();
	}

	const professor* getProfessor(string professorName) {
		std::map<string, professor*>::iterator it = this->professors->find(professorName);
		if (it->first == professorName)
			return it->second;
		throw new professorNotFoundException();
	}

	map<string, professor*>::iterator begin() { return this->professors->begin(); }
	map<string, professor*>::iterator end() { return this->professors->end(); }

	void addProfessor(professor* newProfessor) { this->professors->insert(pair<string, professor*>
		(newProfessor->getName(), newProfessor)); }

	void removeProfessor(string professorName) {
		map<string, professor*>::iterator it = this->professors->find(professorName);
		if ((*it).first == professorName)
			this->professors->erase(it);
		else
			throw new professorNotFoundException();
	}
};