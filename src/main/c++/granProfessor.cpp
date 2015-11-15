#include "stdafx.h"
#include "granProfessor.h"
#include "modelExceptions.h"

using namespace std;

granProfessor::granProfessor(){
	this->memberName = "";	//Member Name
	this->primaryDomain = "";	//Primary Domain
	this->numberOfGrants = 0;	//Number of entries in all vectors
	this->type = new vector<string>();
	this->startDate = new vector<int>();
	this->endDate = new vector<int>();
	this->grantStatus = new vector<string>();
	this->peerReviewed = new vector<bool>();
	this->industryGrant = new vector<bool>();
	this->role = new vector<string>();
	this->title = new vector<string>();
	this->principalInvestigator = new vector<string>();
	this->coInvestigators = new vector<string>();
	this->fundingAmount = new vector<float>();
}
granProfessor::granProfessor(string memberName, string primaryDomain){
	granProfessor();
	this->memberName = memberName;	//Member Name
	this->primaryDomain = primaryDomain;	//Primary Domain
	this->numberOfGrants = 0;	//Number of entries in all vectors
}
granProfessor::~granProfessor(){
	delete this->type;
	delete this->startDate;
	delete this->endDate;
	delete this->grantStatus;
	delete this->peerReviewed;
	delete this->industryGrant;
	delete this->role;
	delete this->title;
	delete this->principalInvestigator;
	delete this->coInvestigators;
	delete this->fundingAmount;
}

const string granProfessor::getName(){ return this->memberName; }
const string granProfessor::getDomain(){ return this->primaryDomain; }
const int granProfessor::getNumberOfGrants(){ return this->numberOfGrants; }

const vector<string>* granProfessor::getType() { return this->type; }
const vector<int>* granProfessor::getStartDate(){ return this->startDate; }
const vector<int>* granProfessor::getEndDate(){ return this->endDate; }
const vector<string>* granProfessor::getGrantStatus(){ return this->grantStatus; }
const vector<bool>* granProfessor::getPeerReviewed(){ return this->peerReviewed; }
const vector<bool>* granProfessor::getIndustryGrant(){ return this->industryGrant; }
const vector<string>* granProfessor::getRole(){ return this->role; }
const vector<string>* granProfessor::getTitle(){ return this->title; }
const vector<string>* granProfessor::getPrincipalInvestigator(){ return this->principalInvestigator; }
const vector<string>* granProfessor::getCoInvestigators(){ return this->coInvestigators; }
const vector<float>* granProfessor::getFundingAmount(){ return this->fundingAmount; }

//Add an entry to all vectors
void granProfessor::addEntry(int startDate, int endDate, string type, string grantStatus, bool peerReviewed,
		bool industryGrant, string role, string title, string principalInvestigator, string coInvestigator, float fundingAmount){
	this->numberOfGrants++;
	this->type->push_back(type);
	this->startDate->push_back(startDate);
	this->endDate->push_back(endDate);
	this->grantStatus->push_back(grantStatus);
	this->peerReviewed->push_back(peerReviewed);
	this->industryGrant->push_back(industryGrant);
	this->role->push_back(role);
	this->title->push_back(title);
	this->principalInvestigator->push_back(principalInvestigator);
	this->coInvestigators->push_back(coInvestigator);
	this->fundingAmount->push_back(fundingAmount);
}

//Remove an entry, based on given index value (0 indexed)
void granProfessor::removeEntry(int indexToRemove){
	if (indexToRemove >= this->numberOfGrants)
		throw new indexOutOfBoundsException();

	this->numberOfGrants--;
	this->type->erase(type->begin()+indexToRemove);
	this->startDate->erase(startDate->begin() + indexToRemove);
	this->endDate->erase(endDate->begin() + indexToRemove);
	this->grantStatus->erase(grantStatus->begin() + indexToRemove);
	this->peerReviewed->erase(peerReviewed->begin() + indexToRemove);
	this->industryGrant->erase(industryGrant->begin() + indexToRemove);
	this->role->erase(role->begin() + indexToRemove);
	this->title->erase(title->begin() + indexToRemove);
	this->principalInvestigator->erase(principalInvestigator->begin() + indexToRemove);
	this->coInvestigators->erase(coInvestigators->begin() + indexToRemove);
	this->fundingAmount->erase(fundingAmount->begin() + indexToRemove);
}