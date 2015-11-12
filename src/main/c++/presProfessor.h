#pragma once
#include <string>
#include <vector>

using namespace std;

class presProfessor {
private:
	string memberName;	//Member Name
	string primaryDomain;	//Primary Domain
	int numberOfPresentations;	//Number of entries in all vectors

	vector<int>* date;
	vector<string>* type;
	vector<string>* role;
	vector<string>* title;
public:
	presProfessor();
	presProfessor(string memberName, string primaryDomain);
	virtual ~presProfessor();

	const string getName();
	const string getDomain();
	const int getNumberOfPres();
	const vector<string>* getType();
	const vector<string>* getRole();
	const vector<string>* getTitle();
	const vector<int>* getDate();

	void addEntry(string type, string role, string title, int date);
	void removeEntry(int indexToRemove);
	vector<pair<string, int>*>* getStatistics();
};