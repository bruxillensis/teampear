#pragma once
#include <string>
#include <vector>
#include "pubProfessor.h"
#include "errorHandling.h"
/** Not currently implemented
#include "granProfessor.h"
#include "teacProfessor.h"
#include "presProfessor.h"
*/

using namespace std;

template<class T>
class createProfessor {
public:
	//Create professor object, filling in all information and pass reference back
	//This function should retrieve all relivant rows from csv 2D array and pass to appropriate private construct function
	createProfessor();
	static T* createNewProfessor(vector<vector<string>>& csv);
private:
	//Should create professor objects of particular professor type and return a professor of that type
	static pubProfessor* createNewPubProfessor(vector<vector<string>>& csv);

	/** Not currently implemented//
	static granProfessor* createNewGrantProfessor(string professorName, vector<vector<string>>& csv);
	static teacProfessor* createNewTeachingProfessor(string professorName, vector<vector<string>>& csv);
	static presProfessor* createNewPresProfessor(string professorName, vector<vector<string>>& csv);
	*/
};

template <class T>
T* createProfessor<T>::createNewProfessor(vector<vector<string>>& csv){
	//If type is of pubProfessor do
	//Requires C++11 to use is_same
	if (std::is_same<T, pubProfessor>::value){
		return createNewPubProfessor(csv);
	}
	//If type is of teachProfessor do

	//If type is of granProfessor do

	//If type is of presProfessor do

}

template <class T>
pubProfessor* createProfessor<T>::createNewPubProfessor(vector<vector<string>>& csv){
	pubProfessor* newProf = new pubProfessor(csv[1][4], csv[1][5]);
	int entries = csv.size();//Total number of entries in csv
	int currLine = 1; //current line being checked

	vector<string> manFields = { "Member Name", "Primary Domain", "Publication Status", "Type", "Status Date", "Role", "Journal Name | Published In | Book Title | etc.", "Author(s)", "Title" };

	while (currLine < entries){ //Search every entry of csv
		//Get all the values for the entry method from csv
		//if (!checkRow(csv[currLine], csv[0], manFields))
		//	continue;
		string pubStatus, pubType, pubRole, pubName, pubAuthors, pubTitle;
		pubStatus = csv[currLine][6];
		pubType = csv[currLine][8];
		pubRole = csv[currLine][11];
		pubName = csv[currLine][15];
		pubAuthors = csv[currLine][37];
		pubTitle = csv[currLine][38];
		//Add the new entry to the prof
		newProf->addEntry(pubStatus, pubType, pubRole, pubName, pubAuthors, pubTitle);

		//Move to the next entry
		currLine++;
	}
	//Return the new professor after all entries have been added
	return newProf;

}

