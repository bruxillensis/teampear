#pragma once
#include <string>

using namespace std;

class pubProfessor {
private:
	string memberName;
	string primaryDomain;
	vector<string>* publicationStatus;
	vector<string>* type;
	vector<string>* role;
	vector<string>* publicationName;
	vector<string>* authors;
	vector<string>* title;
public:
	pubProfessor();
	pubProfessor(string memberName, string primaryDomain);

	//get & set (should be CONST!) operations
};