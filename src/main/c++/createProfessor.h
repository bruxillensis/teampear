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
