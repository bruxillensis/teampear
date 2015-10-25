#pragma once
#include <string>

using namespace std;

class pubProfessor {
private:
	string memberName;	//Member Name
	string primaryDomain;	//Primary Domain
	int numberOfPublications;	//Number of entries in all vectors

	//All vectors can be identifed by array operations (ex. getType()[i];)
	vector<string>* publicationStatus;
	vector<string>* type;
	vector<string>* role;
	vector<string>* publicationName;
	vector<string>* authors;
	vector<string>* title;
public:
	pubProfessor();
	pubProfessor(string memberName, string primaryDomain);
	virtual ~pubProfessor();

	const string getName();
	const string getDomain();
	const int getNumberOfPubs();
	const vector<string>* getPublicationStatus();
	const vector<string>* getType();
	const vector<string>* getRole();
	const vector<string>* getPublicationName();
	const vector<string>* getAuthors();
	const vector<string>* getTitle();

	void addEntry(string publicationStatus, string type, string role, string publicationName, string authors, string title);
	void removeEntry(int indexToRemove);
};
