#include "stdafx.h"
#include "presProfessor.h"
#include "modelExceptions.h"

using namespace std;

presProfessor::presProfessor(){
	this->memberName = "";
	this->primaryDomain = "";
	this->numberOfPresentations = 0;
	this->type = new vector<string>();
	this->role = new vector<string>();
	this->title = new vector<string>();
	this->date = new vector<int>();
}
presProfessor::presProfessor(string memberName, string primaryDomain){
	presProfessor();
	this->memberName = memberName;
	this->primaryDomain = primaryDomain;
}
presProfessor::~presProfessor(){
	delete this->type;
	delete this->role;
	delete this->title;
	delete this->date;
}

const string presProfessor::getName(){ return this->memberName; }
const string presProfessor::getDomain(){ return this->primaryDomain; }
const int presProfessor::getNumberOfPres(){ return this->numberOfPresentations; }
const vector<string>* presProfessor::getType(){ return this->type; }
const vector<string>* presProfessor::getRole(){ return this->role; }
const vector<string>* presProfessor::getTitle(){ return this->title; }
const vector<int>* presProfessor::getDate(){ return this->date; }

void presProfessor::addEntry(string type, string role, string title, int date){
	this->numberOfPresentations++;
	this->type->push_back(type);
	this->role->push_back(role);
	this->title->push_back(title);
	this->date->push_back(date);
}
void presProfessor::removeEntry(int indexToRemove){
	if (indexToRemove >= this->numberOfPresentations)
		throw new indexOutOfBoundsException();

	this->numberOfPresentations--;
	this->type->erase(type->begin() + indexToRemove);
	this->date->erase(date->begin() + indexToRemove);
	this->role->erase(role->begin() + indexToRemove);
	this->title->erase(title->begin() + indexToRemove);
}