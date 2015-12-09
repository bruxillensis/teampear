#pragma once
#include <QErrorMessage>
#include <QString>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include "createProfessor.h"

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
	professorMap(string fileName) {
		this->professors = new map<string, professor*>();
		this->importCSV(fileName);
	}
	virtual ~professorMap() {
		for (auto& it : *professors)
			delete it.second;
		delete professors;
	}

	//parses a CSV file into a 2D vector of strings
	void ParseCSV(string fileName, vector<vector<string> *>& lines)
	{
		ifstream myfile(fileName);
		string csvSource;

		if (myfile.is_open())
		{
			bool inQuote(false);
			bool newLine(false);
			string field;
			vector<string>* line = new vector<string>();

			//reads lines (aka up to the next \n character)
			while (getline(myfile, csvSource)){
				csvSource = "\n" + csvSource;
				string::const_iterator aChar = csvSource.begin();
				while (aChar != csvSource.end())
				{
					switch (*aChar)
					{
					case '"':
						newLine = false;
						inQuote = !inQuote;
						break;

					case ',':
						newLine = false;
						//checks for quote-embedded commas
						if (inQuote == true)
						{
							field += *aChar;
						}
						else
						{
							line->push_back(field);
							field.clear();
						}
						break;

					case '\n':
					case '\r':
						//checks for embedded newlines
						if (inQuote == true)
						{
							field += *aChar;
						}
						break;

					default:
						newLine = false;
						field.push_back(*aChar);
						break;
					}

					aChar++;
				}

				//one field, not in a quote
				if (field.size() && !inQuote){
					line->push_back(field);
					field.clear();
				}

				//new line character that is not in a quote
				if (line->size() && !inQuote){
					lines.push_back(line);
					line = new vector<string>();
				}
			}
			myfile.close();
		}
	}

	//prints out a 2D vector
	//used for testing purposes
	void printVector(vector<vector<string>*>& lines){
		for (size_t i = 0; i < lines.size(); i++) {
			for (size_t j = 0; j < lines.at(i)->size(); j++) {
				cout << i << " " << j << ": " << lines.at(i)->at(j);
				cout << '\n';
			}
		}
	}

	/*
	Should import csv by creating 'virtualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.

	Returns the professor type made.
	*/
	profType importCSV(string fileName) {
		//read CSV file into 2D array
		vector<vector<string>*> myCSV;
		ParseCSV(fileName, myCSV);

		//determine what type of professor should be made
		profType type;
		vector<string> mName;
		vector<int> test;

		//test for publication
		mName.push_back("Publication Status");
		test = createProfessor::findHeaders(mName, *(myCSV.at(0)));
		if (test.size() != 0){
			type = Publication;
			mName.clear();
			test.clear();
		}
		else{
			//test for presentation
			mName.clear();
			test.clear();
			mName.push_back("Date");
			test = createProfessor::findHeaders(mName, *(myCSV.at(0)));
			if (test.size() != 0){
				type = Presentation;
			}
			else{
				//test for grants
				mName.clear();
				test.clear();
				mName.push_back("Industry Grant?");
				test = createProfessor::findHeaders(mName, *(myCSV.at(0)));
				if (test.size() != 0){
					type = GrantClinical;
				}
				else{
					//test for teaching
					mName.clear();
					test.clear();
					mName.push_back("Program");
					test = createProfessor::findHeaders(mName, *(myCSV.at(0)));
					if (test.size() != 0){
						type = Teaching;
					}
				}
			}
		}

		if (type != Teaching || type != Publication || type != GrantClinical || type != Presentation){
			throw typeNotRecognizedException();
		}

		map<string, vector<vector<string> > >* orgCSV = new map<string, vector<vector<string> > >();

		//Find the index of the Member Name
		//Works only if the name field is named "Member Name"
		mName.clear();
		mName.push_back("Member Name");
		vector<int> indexMemberName = createProfessor::findHeaders(mName, *(myCSV.at(0)));

		//Populate the Map
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
		int errCount = 0;
		for (map<string, vector<vector<string> > >::iterator it = orgCSV->begin(); it != orgCSV->end(); ++it) {
			pair<professor*, int> prof;
			try{
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
			}
			catch (manditoryHeaderNotFoundException& e){
				throw manditoryHeaderNotFoundException();
			}
			this->professors->insert(pair<string, professor*>(prof.first->getName(), prof.first));
			errCount += prof.second;
		}
		ostringstream convert;
		convert << errCount;
		string result = "Rows Not Imported Due to Errors: " + convert.str();

		QErrorMessage msg;
		msg.showMessage(QString(result.c_str()));
		msg.exec();
		for (size_t i = 0; i < myCSV.size(); i++)
			delete myCSV[i];
		delete orgCSV;

		return type;
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

	professor* getProfessor(string professorName) {
		std::map<string, professor*>::iterator it = this->professors->find(professorName);
		if (it->first == professorName)
			return it->second;
		throw new professorNotFoundException();
	}

	map<string, professor*>::iterator begin() { return this->professors->begin(); }
	map<string, professor*>::iterator end() { return this->professors->end(); }

	void addProfessor(professor* newProfessor) {
		this->professors->insert(pair<string, professor*>
			(newProfessor->getName(), newProfessor));
	}

	void removeProfessor(string professorName) {
		map<string, professor*>::iterator it = this->professors->find(professorName);
		if ((*it).first == professorName)
			this->professors->erase(it);
		else
			throw new professorNotFoundException();
	}
};