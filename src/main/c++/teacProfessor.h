#pragma once
#include <string>
#include <vector>

using namespace std;

class teacProfessor {
private:
	string memberName;	//Member Name
	string primaryDomain;	//Primary Domain
	int numberOfClasses;	//Number of entries in all vectors

	vector<int>* startDate;
	vector<int>* endDate;
	vector<string>* program;
	vector<string>* courseType;
	vector<string>* course;
	vector<string>* geoScope;
	vector<float>* hoursPerSession;
	vector<int>* numberOfSessions;
	vector<float>* totalHours;

public:
	teacProfessor();
	teacProfessor(string memberName, string primaryDomain);
	virtual ~teacProfessor();

	const string getName();
	const string getDomain();
	const int getNumberOfClasses();
	const vector<int>* getStartDate();
	const vector<int>* getEndDate();
	const vector<string>* getProgram();
	const vector<string>* getCourseType();
	const vector<string>* getCourse();
	const vector<string>* getGeoScope();
	const vector<float>* getHoursPerSession();
	const vector<int>* getNumberOfSessions();
	const vector<float>* getTotalHours();

	void addEntry(int startDate, int endDate, string program, string courseType, string course, string geoScope,
		float hoursPerSession, int numberOfSessions, float totalHours);
	void removeEntry(int indexToRemove);
	vector<pair<string, int>*>* getStatistics();
};