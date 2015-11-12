#include "stdafx.h"
#include "teacProfessor.h"
#include "modelExceptions.h"

using namespace std;

teacProfessor::teacProfessor(){
	this->memberName = "";
	this->primaryDomain = "";
	this->numberOfClasses = 0;
	this->startDate = new vector<int>();
	this->endDate = new vector<int>();
	this->program = new vector<string>();
	this->courseType = new vector<string>();
	this->course = new vector<string>();
	this->geoScope = new vector<string>();
	this->hoursPerSession = new vector<float>();
	this->numberOfSessions = new vector<int>();
	this->totalHours = new vector<float>();
}
teacProfessor::teacProfessor(string memberName, string primaryDomain){
	teacProfessor();
	this->memberName = memberName;
	this->primaryDomain = primaryDomain;
}
teacProfessor::~teacProfessor(){
	delete this->startDate;
	delete this->endDate;
	delete this->program;
	delete this->courseType;
	delete this->course;
	delete this->geoScope;
	delete this->hoursPerSession;
	delete this->numberOfSessions;
	delete this->totalHours;
}

const string teacProfessor::getName(){ return this->memberName; }
const string teacProfessor::getDomain(){ return this->primaryDomain; }
const int teacProfessor::getNumberOfClasses(){ return this->numberOfClasses; }
const vector<int>* teacProfessor::getStartDate(){ return this->startDate; }
const vector<int>* teacProfessor::getEndDate(){ return this->endDate; }
const vector<string>* teacProfessor::getProgram(){ return this->program; }
const vector<string>* teacProfessor::getCourseType(){ return this->courseType; }
const vector<string>* teacProfessor::getCourse(){ return this->course; }
const vector<string>* teacProfessor::getGeoScope(){ return this->geoScope; }
const vector<float>* teacProfessor::getHoursPerSession(){ return this->hoursPerSession; }
const vector<int>* teacProfessor::getNumberOfSessions(){ return this->numberOfSessions; }
const vector<float>* teacProfessor::getTotalHours(){ return this->totalHours; }

void teacProfessor::addEntry(int startDate, int endDate, string program, string courseType, string course, string geoScope,
		float hoursPerSession, int numberOfSessions, float totalHours){
	this->numberOfClasses++;
	this->startDate->push_back(startDate);
	this->endDate->push_back(endDate);
	this->program->push_back(program);
	this->courseType->push_back(courseType);
	this->course->push_back(course);
	this->geoScope->push_back(geoScope);
	this->hoursPerSession->push_back(hoursPerSession);
	this->numberOfSessions->push_back(numberOfSessions);
	this->totalHours->push_back(totalHours);
}
void teacProfessor::removeEntry(int indexToRemove){
	if (indexToRemove >= this->numberOfClasses)
		throw new indexOutOfBoundsException();

	this->numberOfClasses--;
	this->startDate->erase(startDate->begin()+indexToRemove);
	this->endDate->erase(endDate->begin() + indexToRemove);
	this->program->erase(program->begin() + indexToRemove);
	this->courseType->erase(courseType->begin() + indexToRemove);
	this->course->erase(course->begin() + indexToRemove);
	this->geoScope->erase(geoScope->begin() + indexToRemove);
	this->hoursPerSession->erase(hoursPerSession->begin() + indexToRemove);
	this->numberOfSessions->erase(numberOfSessions->begin() + indexToRemove);
	this->totalHours->erase(totalHours->begin() + indexToRemove);
}