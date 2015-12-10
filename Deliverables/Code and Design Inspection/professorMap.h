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
#include "csv.h"


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
		io::CSVReader<44, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> inFile(fileName);
		string temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, \
			temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24, temp25, temp26, temp27, temp28, temp29, temp30, temp31, temp32, \
			temp33, temp34, temp35, temp36, temp37, temp38, temp39, temp40, temp41, temp42, temp43, temp44;

		while (inFile.read_row(temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11, temp12, temp13, temp14, temp15, temp16, \
			temp17, temp18, temp19, temp20, temp21, temp22, temp23, temp24, temp25, temp26, temp27, temp28, temp29, temp30, temp31, temp32, \
			temp33, temp34, temp35, temp36, temp37, temp38, temp39, temp40, temp41, temp42, temp43, temp44)) {
			//killme
			valueLine = new vector<string>();
			valueLine->push_back(temp1);
			valueLine->push_back(temp2);
			valueLine->push_back(temp3);
			valueLine->push_back(temp4);
			valueLine->push_back(temp5);
			valueLine->push_back(temp6);
			valueLine->push_back(temp7);
			valueLine->push_back(temp8);
			valueLine->push_back(temp9);
			valueLine->push_back(temp10);
			valueLine->push_back(temp11);
			valueLine->push_back(temp12);
			valueLine->push_back(temp13);
			valueLine->push_back(temp14);
			valueLine->push_back(temp15);
			valueLine->push_back(temp16);
			valueLine->push_back(temp17);
			valueLine->push_back(temp18);
			valueLine->push_back(temp19);
			valueLine->push_back(temp20);
			valueLine->push_back(temp21);
			valueLine->push_back(temp22);
			valueLine->push_back(temp23);
			valueLine->push_back(temp24);
			valueLine->push_back(temp25);
			valueLine->push_back(temp26);
			valueLine->push_back(temp27);
			valueLine->push_back(temp28);
			valueLine->push_back(temp29);
			valueLine->push_back(temp30);
			valueLine->push_back(temp31);
			valueLine->push_back(temp32);
			valueLine->push_back(temp33);
			valueLine->push_back(temp34);
			valueLine->push_back(temp35);
			valueLine->push_back(temp36);
			valueLine->push_back(temp37);
			valueLine->push_back(temp38);
			valueLine->push_back(temp39);
			valueLine->push_back(temp40);
			valueLine->push_back(temp41);
			valueLine->push_back(temp42);
			valueLine->push_back(temp43);
			valueLine->push_back(temp44);
			myCSV.push_back(valueLine);
		}

		for (size_t i = 0; i < 10; i++) {
			for (size_t j = 0; j < myCSV[i]->size(); j++) {
				cout << i << " " << j << ": " << myCSV[i]->at(j);
				cout << '\n';
			}
		}

		map<string, vector<vector<string> > >* orgCSV = new map<string, vector<vector<string> > >();
		for (size_t i = 1; i < myCSV.size(); i++) {

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
	vector<pair<string,vector<pair<string,int> > > > callMe(int begYear, int endYear) {
		//	T* prof;
		vector<pair<string, vector<pair<string, int> > > > mainVector;

		vector<pair<string, int> >* vBookChapters = new vector<pair<string, int>>;
		vector<pair<string, int> >* vBooks = new vector<pair<string, int>>;
		vector<pair<string, int> >* vBookEdits = new vector<pair<string, int>>;
		vector<pair<string, int> >* vCaseReports = new vector<pair<string, int>>;
		vector<pair<string, int> >* vClinicalCareGuides = new vector<pair<string, int>>;
		vector<pair<string, int> >* vCommentaries = new vector<pair<string, int>>;
		vector<pair<string, int> >* vConferences = new vector<pair<string, int>>;
		vector<pair<string, int> >* vEditorials = new vector<pair<string, int>>;
		vector<pair<string, int> >* vInvitedArticles = new vector<pair<string, int>>;
		vector<pair<string, int> >* vJournalArticles = new vector<pair<string, int>>;
		vector<pair<string, int> >* vLetters = new vector<pair<string, int>>;
		vector<pair<string, int> >* vMagazine = new vector<pair<string, int>>;
		vector<pair<string, int> >* vManuals = new vector<pair<string, int>>;
		vector<pair<string, int> >* vMonograph = new vector<pair<string, int>>;
		vector<pair<string, int> >* vMultimedia = new vector<pair<string, int>>;
		vector<pair<string, int> >* vNewsletterArt = new vector<pair<string, int>>;
		vector<pair<string, int> >* vNewspaperArt = new vector<pair<string, int>>;
		vector<pair<string, int> >* vAbstracts = new vector<pair<string, int>>;
		vector<pair<string, int> >* vStudentPubs = new vector<pair<string, int>>;
		vector<pair<string, int> >* vWebVids = new vector<pair<string, int>>;
		vector<pair<string, int> >* vWorkingPapers = new vector<pair<string, int>>;

		const char* args[] = { "Book Chapters", "Books", "Books Edited", "Case Reports", "Clinical Case Guidelines", \
			"Commentaries", "Conference Proceedings", "Editorials", "Invited Articles", "Journal Article", \
			"Letters to Editor", "Magazine Entries", "Manuals", "Monographs", "Multimedia", "Newsletter Articles", \
			"Newspaper Articles", "Published Abstracts", "Supervised Student Publications", "Websites / Videos", \
			"Working Papers" };

		vector<string> type(args, args + sizeof(args) / sizeof(args[0]));
		map<string, T*>::iterator it;
		for (it = professors->begin(); it != professors->end(); ++it) {
			const vector <string>* pubTypes = it->second->getType();
			const vector <int>* pubDates = it->second->getDate();
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
			int countMonographs = 0;
			int countMultimedia = 0;
			int countNewsletterArticles = 0;
			int countNewspaperArticles = 0;
			int countAbstracts = 0;
			int countStudentPubs = 0;
			int countWebVids = 0;
			int countWorkingPapers = 0;

			vector<int>::const_iterator it3 = pubDates->begin();
			for (vector<string>::const_iterator it2 = pubTypes->begin(); it2 != pubTypes->end(); ++it2) { // iterate through the publication types
				if ((!(*it2).compare(type[0]))&&((*it3)>begYear&& (*it3)<endYear))
					countBookChapters++;
				else if ((!(*it2).compare(type[1])) && ((*it3)>begYear && (*it3)<endYear))
					countBooks++;
				else if ((!(*it2).compare(type[2])) && ((*it3)>begYear && (*it3)<endYear))
					countBookEdits++;
				else if ((!(*it2).compare(type[3])) && ((*it3)>begYear && (*it3)<endYear))
					countCaseReports++;
				else if ((!(*it2).compare(type[4])) && ((*it3)>begYear && (*it3)<endYear))
					countClinicalCareGuides++;
				else if ((!(*it2).compare(type[5])) && ((*it3)>begYear && (*it3)<endYear))
					countCommentaries++;
				else if ((!(*it2).compare(type[6])) && ((*it3)>begYear && (*it3)<endYear))
					countConferences++;
				else if ((!(*it2).compare(type[7])) && ((*it3)>begYear && (*it3)<endYear))
					countEditorials++;
				else if ((!(*it2).compare(type[8])) && ((*it3)>begYear && (*it3)<endYear))
					countInvitedArticles++;
				else if ((!(*it2).compare(type[9])) && ((*it3)>begYear && (*it3)<endYear))
					countJournalArticles++;
				else if ((!(*it2).compare(type[10])) && ((*it3)>begYear && (*it3)<endYear))
					countLetters++;
				else if ((!(*it2).compare(type[11])) && ((*it3)>begYear && (*it3)<endYear))
					countMagazine++;
				else if ((!(*it2).compare(type[12])) && ((*it3)>begYear && (*it3)<endYear))
					countManuals++;
				else if ((!(*it2).compare(type[13])) && ((*it3)>begYear && (*it3)<endYear))
					countMonographs++;
				else if ((!(*it2).compare(type[14])) && ((*it3)>begYear && (*it3)<endYear))
					countMultimedia++;
				else if ((!(*it2).compare(type[15])) && ((*it3)>begYear && (*it3)<endYear))
					countNewsletterArticles++;
				else if ((!(*it2).compare(type[16])) && ((*it3)>begYear && (*it3)<endYear))
					countNewspaperArticles++;
				else if ((!(*it2).compare(type[17])) && ((*it3)>begYear && (*it3)<endYear))
					countAbstracts++;
				else if ((!(*it2).compare(type[18])) && ((*it3)>begYear && (*it3)<endYear))
					countStudentPubs++;
				else if ((!(*it2).compare(type[19])) && ((*it3)>begYear && (*it3)<endYear))
					countWebVids++;
				else if ((!(*it2).compare(type[20])) && ((*it3)>begYear && (*it3)<endYear))
					countWorkingPapers++;
				++it3;
			}

			//make pairs and push into vectors
			pair<string, int>* temp;

			temp = new pair<string, int>(profName, countBookChapters);
			vBookChapters->push_back(*temp);

			temp = new pair<string, int>(profName, countBooks);
			vBooks->push_back(*temp);

			temp = new pair<string, int>(profName, countCaseReports);
			vCaseReports->push_back(*temp);

			temp = new pair<string, int>(profName, countClinicalCareGuides);
			vClinicalCareGuides->push_back(*temp);

			temp = new pair<string, int>(profName, countCommentaries);
			vCommentaries->push_back(*temp);

			temp = new pair<string, int>(profName, countConferences);
			vConferences->push_back(*temp);

			temp = new pair<string, int>(profName, countEditorials);
			vEditorials->push_back(*temp);

			temp = new pair<string, int>(profName, countInvitedArticles);
			vInvitedArticles->push_back(*temp);

			temp = new pair<string, int>(profName, countJournalArticles);
			vJournalArticles->push_back(*temp);

			temp = new pair<string, int>(profName, countLetters);
			vLetters->push_back(*temp);

			temp = new pair<string, int>(profName, countMagazine);
			vMagazine->push_back(*temp);

			temp = new pair<string, int>(profName, countManuals);
			vManuals->push_back(*temp);

			temp = new pair<string, int>(profName, countMonographs);
			vMonograph->push_back(*temp);

			temp = new pair<string, int>(profName, countMultimedia);
			vMultimedia->push_back(*temp);

			temp = new pair<string, int>(profName, countNewsletterArticles);
			vNewsletterArt->push_back(*temp);

			temp = new pair<string, int>(profName, countNewspaperArticles);
			vNewspaperArt->push_back(*temp);

			temp = new pair<string, int>(profName, countAbstracts);
			vAbstracts->push_back(*temp);

			temp = new pair<string, int>(profName, countStudentPubs);
			vStudentPubs->push_back(*temp);

			temp = new pair<string, int>(profName, countWebVids);
			vWebVids->push_back(*temp);

			temp = new pair<string, int>(profName, countWorkingPapers);
			vWorkingPapers->push_back(*temp);
		}

		//push 15 publication type vectors into pairs

		pair<string, vector<pair<string, int> > >* temporary;

		temporary = new pair<string, vector<pair<string, int> > >(type[0], *vBookChapters);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[1], *vBooks);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[2], *vBookEdits);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[3], *vCaseReports);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[4], *vClinicalCareGuides);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[5], *vCommentaries);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[6], *vConferences);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[7], *vEditorials);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[8], *vInvitedArticles);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[9], *vJournalArticles);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[10], *vLetters);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[11], *vMagazine);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[12], *vManuals);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[13], *vMonograph);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[14], *vMultimedia);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[15], *vNewsletterArt);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[16], *vNewspaperArt);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[17], *vAbstracts);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[18], *vStudentPubs);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[19], *vWebVids);
		mainVector.push_back(*temporary);

		temporary = new pair<string, vector<pair<string, int> > >(type[20], *vWorkingPapers);
		mainVector.push_back(*temporary);

		return mainVector;
	}
};
