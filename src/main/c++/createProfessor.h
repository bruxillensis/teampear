#pragma once
#include <string>
#include <vector>
#include "errorHandling.h"
#include "granProfessor.h"
#include "teacProfessor.h"
#include "presProfessor.h"
#include "pubProfessor.h"
#include "modelExceptions.h"

using namespace std;

template<class T>
class createProfessor {
public:
	//Create professor object, filling in all information and pass reference back
	//This function should retrieve all relivant rows from csv 2D array and pass to appropriate private construct function
	static T* createNewProfessor(vector<vector<string>>& csv) {
		//Requires C++11 to use is_same
		//If type is of pubProfessor do
		if (std::is_same<T, pubProfessor>::value) {
			return (T*) createNewPubProfessor(csv);
		}
		//If type is of teachProfessor do
		if (std::is_same<T, teacProfessor>::value) {
			return (T*) createNewTeacProfessor(csv);
		}
		//If type is of granProfessor do
		if (std::is_same<T, granProfessor>::value) {
			return (T*) createNewGranProfessor(csv);
		}
		//If type is of presProfessor do
		if (std::is_same<T, presProfessor>::value) {
			return (T*) createNewPresProfessor(csv);
		}
	}
private:
	//Should create professor objects of particular professor type and return a professor of that type
	static pubProfessor* createNewPubProfessor(vector<vector<string>>& csv) {
		vector<string> manFields = {"Member Name", "Primary Domain", "Publication Status", "Type", "Status Date",
			"Role", "Journal Name | Published In | Book Title | etc.", "Author(s)", "Title" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);

		pubProfessor* newProf = new pubProfessor(csv[1][headerNumbers[0]], csv[1][headerNumbers[1]]);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try {
				errorHandling::checkRow(csv[i], csv[0], manFields);
				newProf->addEntry(csv[i][headerNumbers[2]], csv[i][headerNumbers[3]],
					errorHandling::checkYear(csv[i][headerNumbers[4]]),
					csv[i][headerNumbers[5]], csv[i][headerNumbers[6]],
					csv[i][headerNumbers[7]], csv[i][headerNumbers[8]]);
			}
			catch (emptyManditoryCellException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
		}
		//Return the new professor after all entries have been added
		return newProf;
	}
	static granProfessor* createNewGranProfessor(vector<vector<string>>& csv){
		vector<string> manFields = { "Member Name", "Primary Domain", "Start Date", "End Date", "Funding Type", "Status",
			"Peer Reviewed?", "Industry Grant?", "Role", "Title",
			"Principal Investigator", "Co-Investigators", "Total Amount" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);

		granProfessor* newProf = new granProfessor(csv[1][headerNumbers[0]], csv[1][headerNumbers[1]]);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				errorHandling::checkRow(csv[i], csv[0], manFields);
				newProf->addEntry(
					errorHandling::checkYear(csv[i][headerNumbers[2]]),
					errorHandling::checkYear(csv[i][headerNumbers[3]]),
					csv[i][headerNumbers[4]], csv[i][headerNumbers[5]],
					errorHandling::toBool(csv[i][headerNumbers[6]]),
					errorHandling::toBool(csv[i][headerNumbers[7]]),
					csv[i][headerNumbers[8]], csv[i][headerNumbers[9]],
					csv[i][headerNumbers[10]], csv[i][headerNumbers[11]],
					errorHandling::toFloat(csv[i][headerNumbers[12]]));
			}
			catch (emptyManditoryCellException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
		}
		//Return the new professor after all entries have been added
		return newProf;
	}
	static teacProfessor* createNewTeacProfessor(vector<vector<string>>& csv){
		vector<string> manFields = { "Member Name", "Primary Domain", "Start Date", "End Date", "Program", "Type of Course / Activity",
			"Course / Activity", "Geographical Scope", "Hours per Teaching Session or Week",
			"Number of Teaching Sessions or Weeks", "Total Amount" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);

		teacProfessor* newProf = new teacProfessor(csv[1][headerNumbers[0]], csv[1][headerNumbers[1]]);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				errorHandling::checkRow(csv[i], csv[0], manFields);
				newProf->addEntry(errorHandling::checkYear(csv[i][headerNumbers[2]]),
					errorHandling::checkYear(csv[i][headerNumbers[3]]),
					csv[i][headerNumbers[7]], csv[i][headerNumbers[5]],
					csv[i][headerNumbers[6]], csv[i][headerNumbers[7]],
					errorHandling::toFloat(csv[i][headerNumbers[8]]),
					errorHandling::toInt(csv[i][headerNumbers[9]]),
					errorHandling::toFloat(csv[i][headerNumbers[10]]));
			}
			catch (emptyManditoryCellException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
		}
		//Return the new professor after all entries have been added
		return newProf;
	}
	static presProfessor* createNewPresProfessor(vector<vector<string>>& csv){
		vector<string> manFields = { "Member Name", "Primary Domain", "Type", "Role", "Title", "Date" };
		vector<int> headerNumbers = findHeaders(manFields, csv[0]);

		presProfessor* newProf = new presProfessor(csv[1][headerNumbers[0]], csv[1][headerNumbers[1]]);
		for (int i = 1; i < csv.size(); i++) {
			//Add the new entry to the prof
			try{
				errorHandling::checkRow(csv[i], csv[0], manFields);
				newProf->addEntry(csv[i][headerNumbers[1]], csv[i][headerNumbers[2]],
					csv[i][headerNumbers[4]], errorHandling::checkYear(csv[i][headerNumbers[5]]));
			}
			catch (emptyManditoryCellException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
			catch (manditoryHeaderNotFoundException& e){
				//Produce error message when implemented
				cerr << e.what();
			}
		}
		//Return the new professor after all entries have been added
		return newProf;
	}

	static vector<int> findHeaders(vector<string> manFields, vector<string> headers){
		vector<int> returnVec;
		for (int i = 0; i < headers.size(); i++){
			for (int j = 0; j < manFields.size(); j++){
				if (headers[i] == manFields[j]){
					returnVec.push_back(i);
				}
			}
		}
		return returnVec;
	}
};