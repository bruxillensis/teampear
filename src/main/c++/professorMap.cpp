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

vector<pair<string,vector<pair<string,int>>>> callMe(){
	T* prof;
	vector<pair<string,vector<pair<string,int>>>> mainVector;

	vector<pair<string,int>> vBookChapters;
	vector<pair<string,int>> vBooks;
	vector<pair<string,int>> vBookEdits;
	vector<pair<string,int>> vCaseReports;
	vector<pair<string,int>> vClinicalCareGuides;
	vector<pair<string,int>> vCommentaries;
	vector<pair<string,int>> vConferences;
	vector<pair<string,int>> vEditorials;
	vector<pair<string,int>> vInvitedArticles;
	vector<pair<string,int>> vJournalArticles;
	vector<pair<string,int>> vLetters;
	vector<pair<string,int>> vMagazine;
	vector<pair<string,int>> vManuals;
	vector<pair<string,int>> vMonograph;
	vector<pair<string,int>> vMultimedia;
	vector<pair<string,int>> vNewsletterArt;
	vector<pair<string,int>> vNewspaperArt;
	vector<pair<string,int>> vAbstracts;
	vector<pair<string,int>> vStudentPubs;
	vector<pair<string,int>> vWebVids;
	vector<pair<string,int>> vWorkingPapers;

	vector<string> type("Book Chapters","Books","Books Edited","Case Reports","Clinical Case Guidelines",\
		"Commentaries","Conference Proceedings","Editorials","Invited Articles","Journal Articles",\
		"Letters to Editor","Magazine Entries","Manuals","Monographs","Multimedia","Newsletter Articles",\
		"Newspaper Articles","Published Abstracts","Supervised Student Publications","Websites / Videos",\
		"Working Papers")

	for(map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++it){ // iterate through the professor objects
		vector <string> pubTypes = it->second->type);
		string profName = it->first;
		int countBookChapters = 0;
		int countBooks = 0;
		int countBookEdits = 0;
		int countCaseReports = 0;
		int countClinicalCareGuides = 0;
		int countCommentaries = 0;
		int countConferences = 0;
		int countEditorials = 0;
		int countInvitedArticles = 0;
		int countJournalArticles = 0;
		int countLetters = 0;
		int countMagazine = 0;
		int countManuals = 0;
		int countMonograph = 0;
		int countMultimedia = 0;
		int countNewsletterArt = 0;
		int countNewspaperArt = 0;
		int countAbstracts = 0;
		int countStudentPubs = 0;
		int countWebVids = 0;
		int countWorkingPapers = 0;

		for (vector<string>::iterator it2 = pubType.begin(); it2 != pubTypes.end(); ++it2){ // iterate through the publication types
			if (it2 == type[0])
				countBookChapters++;
			else if (it2 == type[1])
				countBooks++;
			else if (it2 == type[2])
				countBookEdits++;
			else if (it2 == type[3])
				coutCaseReports++;
			else if (it2 == type[4])
				countClinicalCareGuides++;
			else if (it2 == type[5])
				countCommentaries++;
			else if (it2 == type[6])
				countConferences++;
			else if (it2 == type[7])
				countEditorials++;
			else if (it2 == type[8])
				countInvitedArticles++;
			else if (it2 == type[9])
				countJournalArticles++;
			else if (it2 == type[10])
				countLetters++;
			else if (it2 == type[11])
				countMagazine++;
			else if (it2 == type[12])
				countManuals++;
			else if (it2 == type[13])
				countMonographs++;
			else if (it2 == type[14])
				countMultimedia++;
			else if (it2 == type[15])
				countNewsletterArticles++;
			else if (it2 == type[16])
				countNewspaperArticles++;
			else if (it2 == type[17])
				countAbstracts++;
			else if (it2 == type[18])
				countStudentPubs++;
			else if (it2 == type[19])
				countWebVids++;
			else if (it2 == type[20])
				countWorkingPapers++;
		}

		//make pairs and push into vectors
		pair<string, int>* temp;

		temp = new pair<string, int> (profName, countBookChapters);
		vBookChapters.push_back(temp);

		temp = new pair<string, int> (profName, countBooks);
		vBooks.push_back(temp);

		temp = new pair<string, int> (profName, countCaseReports);
		vCaseReports.push_back(temp);

		temp = new pair<string, int> (profName, countClinicalCareGuides);
		vClinicalCareGuides .push_back(temp);

		temp = new pair<string, int> (profName, countCommentaries);
		vCommentaries.push_back(temp);

		temp = new pair<string, int> (profName, countConferences);
		vConferences.push_back(temp);

		temp = new pair<string, int> (profName, countEditorials);
		vEditorials.push_back(temp);

		temp = new pair<string, int> (profName, countInvitedArticles);
		vInvitedArticles.push_back(temp);

		temp = new pair<string, int> (profName, countJournalArticles);
		vJournalArticles.push_back(temp);

		temp = new pair<string, int> (profName, countLetters);
		vLetters.push_back(temp);

		temp = new pair<string, int> (profName, countMagazine);
		vMagazine.push_back(temp);

		temp = new pair<string, int> (profName, countManuals);
		vManuals.push_back(temp);

		temp = new pair<string, int> (profName, countMonograph);
		vMonograph.push_back(temp);

		temp = new pair<string, int> (profName, countMultimedia);
		vMultimedia.push_back(temp);

		temp = new pair<string, int> (profName, countNewsletterArt);
		vNewsletterArt.push_back(temp);

		temp = new pair<string, int> (profName, countNewspaperArt);
		vNewspaperArt.push_back(temp);

		temp = new pair<string, int> (profName, countAbstracts);
		vAbstracts.push_back(temp);

		temp = new pair<string, int> (profName, countStudentPubs);
		vStudentPubs.push_back(temp);

		temp = new pair<string, int> (profName, countWebVids);
		vWebVids.push_back(temp);

		temp = new pair<string, int> (profName, countWorkingPapers);
		vWorkingPapers.push_back(temp);
	}

	//push 15 publication type vectors into pairs

	pair<string,vector<pair<string,int>>>* temporary;
	
	temporary = new pair<string,vector<pair<string,int>>>(type[0],countBookChapters);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[1],countBooks);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[2],countBookEdits);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[3],countCaseReports);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[4],countClinicalCareGuides);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[5],countCommentaries);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[6],countConferences);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[7],countEditorials);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[8],countInvitedArticles);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[9],countJournalArticles);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[10],countLetters);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[11],countMagazine);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[12],countManuals);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[13],countMonograph);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[14],countMultimedia);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[15],countNewsletterArt);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[16],countNewspaperArt);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[17],countAbstracts);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[18],countStudentPubs);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[19],countWebVids);
	mainVector.push_back(temporary);
	
	temporary = new pair<string,vector<pair<string,int>>>(type[20],countWorkingPapers);
	mainVector.push_back(temporary);

	return mainVector;
}
