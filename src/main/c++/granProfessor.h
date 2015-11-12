#pragma once
#include <vector>
#include <string>

using namespace std;

class granProfessor{
private:
	string memberName;	//Member Name
	string primaryDomain;	//Primary Domain
	int numberOfGrants;	//Number of grants in all vectors

	vector<string>* type;
	vector<int>* startDate;
	vector<int>* endDate;
	vector<string>* grantStatus;
	vector<bool>* peerReviewed;
	vector<bool>* industryGrant;
	vector<string>* role;
	vector<string>* title;
	vector<string>* principalInvestigator;
	vector<string>* coInvestigators;
	vector<float>* fundingAmount;

public:
	granProfessor();
	granProfessor(string memberName, string primaryDomain);
	virtual ~granProfessor();

	const string getName();
	const string getDomain();
	const int getNumberOfGrants();

	const vector<string>* getType();
	const vector<int>* getStartDate();
	const vector<int>* getEndDate();
	const vector<string>* getGrantStatus();
	const vector<bool>* getPeerReviewed();
	const vector<bool>* getIndustryGrant();
	const vector<string>* getRole();
	const vector<string>* getTitle();
	const vector<string>* getPrincipalInvestigator();
	const vector<string>* getCoInvestigators();
	const vector<float>* getFundingAmount();
	void addEntry(string type, int startDate, int endDate, string grantStatus, bool peerReviewed, bool industryGrant, string role,
		string title, string principalInvestigator, string coInvestigator, float fundingAmount);
	void removeEntry(int indexToRemove);
	vector<pair<string, int>*>* getStatistics();
};