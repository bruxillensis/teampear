#pragma once
#include <string>
#include <vector>
#include "boost/variant.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "modelExceptions.h"

using namespace std;

class professor {
protected:
	//Member Name
	string memberName;
	//Primary Domain
	string primaryDomain;
	//Number of entries in all vectors
	int numberOfEntries;
	//Number of manditory fields
	int numberOfFields;
	//Manditory fields
	vector<vector<boost::variant<int, float, string, bool, boost::gregorian::date>>*>* fields;

public:
	//Empty Constructor
	professor(int numberOfFields){
		this->memberName = "";
		this->primaryDomain = "";
		this->numberOfEntries = 0;
		this->numberOfFields = numberOfFields;
		//Depending on professor type, create number of manditory fields
		this->fields = new vector<vector<boost::variant<int, float, string, bool, boost::gregorian::date>>*>();
		for (int i = 0; i < numberOfFields; i++)
			//Push new vector that can contain int, float, string, bool or date type
			this->fields->push_back(new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>());
	}
	//Non-Empty Constructor
	professor(string memberName, string primaryDomain, int numberOfFields){
		this->memberName = memberName;
		this->primaryDomain = primaryDomain;
		this->numberOfEntries = 0;
		this->numberOfFields = numberOfFields;
		//Depending on professor type, create number of manditory fields
		this->fields = new vector<vector<boost::variant<int, float, string, bool, boost::gregorian::date>>*>();
		for (int i = 0; i < numberOfFields; i++)
			//Push new vector that can contain int, float, string, bool or date type
			this->fields->push_back(new vector<boost::variant<int, float, string, bool, boost::gregorian::date>>());
	}
	//Destructor
	~professor(){
		for (int i = 0; i < fields->size(); i++){
			delete this->fields->at(i);
		}
		delete this->fields;
	}
	//Get professor name
	const string getName(){ return this->memberName; }
	//Get professor domain
	const string getDomain(){ return this->primaryDomain; }
	//Get number of entries for professor
	const int getNumberOfEntries(){ return this->numberOfEntries; }\
	//Return manditory field
	const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* getField(int i){ return fields->at(i); }
	//Add entry
	//Input type is a vector that contains all necessary values for a single entry
	//Types can be a combination of int, float, string, bool and date
	void addEntry(vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* entries){
		if (entries->size() == this->fields->size()){
			this->numberOfEntries++;
			for (int i = 0; i < fields->size();i++){
				this->fields->at(i)->push_back(entries->at(i));
			}
		}
		else
			throw new indexOutOfBoundsException();
	}
	//Removes an entry
	void removeEntry(int j){
		if (j > this->numberOfEntries)
			throw new indexOutOfBoundsException();
		for (int i = 0; i < fields->size(); i++){
			this->fields->at(i)->erase(this->fields->at(i)->begin()+j);
		}
	}
};