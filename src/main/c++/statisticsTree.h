#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "pubProfessor.h"
#include "granProfessor.h"
#include "teacProfessor.h"
#include "presProfessor.h"
#include "professorMap.h"

using namespace std;

/*
Returns organized statistics of a professor type.

ex.
returns for Publications a tree organized like so
	Publications (root)
		Book Chapters
			Prof A, Number of pubs of type Book Chapters
			Prof B, Number of pubs of type Book Chapters
		Books
			Prof A, Number of pubs of type Book
etc.
*/

template <class T>
class statisticsTree {
private:
	node* root;
	void createPubStatistics(professorMap<pubProfessor>* professors){
		//Create Initial Tree
		vector<string> pubTypes;
		root = new node("Publications", 0, 0, 0);

		//Iterate through professors
		for (typename map<string, pubProfessor*>::iterator it = professors->begin(); it != professors->end(); ++it) {
			//Sum statistics and add to tree
			vector<int> typeCount(pubTypes.size(), 0);
			//Iterator through publications
			for (int i = 0; i < it->second->getNumberOfPubs(); i++){
				//Try to find publication in pubTypes
				vector<string>::iterator ti = std::find(pubTypes.begin(), pubTypes.end(), it->second->getType()->at(i));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == presTypes.end()){
					pubTypes.push_back(it->second->getType()->at(i));
					typeCount.push_back(1);
					root->addChild(new node(pubTypes.back(), 0, 0, 0));
				}
				//Else increment count of that type
				else{
					typeCount[std::distance(pubTypes.begin(), ti)]++;
				}
			}
			//Add the professor stats to the tree
			for (int i = 0; i < pubTypes.size(); i++){
				root->getChildren()->at(i)->addChild(new node(it->second->getName(), typeCount[i]));
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (node* &i : root->getChildren()->at(0)->getChildren()){
			int sCount = 0;
			for (node* &j : i->getChildren()){
				sCount += j->second;
			}
			i->setSecond(sCount);
			i->organizeChildren();
			fCount += sCount;
		}
		root->setSecond(fCount);
		root->organizeChildren();
	}
	void createTeacStatistics(professorMap<teacProfessor>* profMap){
		//Create Initial Tree
		vector<string> teachTypes;
		root = new node("Programs", 0, 0, 0);

		for (typename map<string, presProfessor*>::iterator it = professors->begin(); it != professors->end(); ++it) {
			//Sum statistics and add to tree
			vector<int> typeCount(teachTypes.size(), 0);
			//Iterator through class entries
			for (int i = 0; i < it->second->getNumberOfClasses(); i++){
				//Try to find teaching type in teachTypes
				vector<string>::iterator ti = std::find(teachTypes.begin(), teachTypes.end(), it->second->getProgram()->at(i));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == teachTypes.end()){
					teachTypes.push_back(it->second->getProgram()->at(i));
					typeCount.push_back(1);
					root->addChild(new node(teachTypes.back(), 0, 0, 0));
				}
				//Else increment count of that type
				else{
					//Should be added to proper "date" node
					typeCount[std::distance(teachTypes.begin(), ti)]++;
				}
			}
			//Add the professor stats to the tree
			for (int i = 0; i < teachTypes.size(); i++){
				root->getChildren()->at(i)->addChild(new node(it->second->getName(), typeCount[i]));
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (node* &i : root->getChildren()){
			int sCount = 0;
			for (node* &j : i->getChildren()){
				sCount += j->second;
			}
			i->setSecond(sCount);
			i->organizeChildren();
		}
		root->setSecond(fCount);
		root->organizeChildren();
	}
	void createGranStatistics(professorMap<granProfessor>* professors){
		
		//Create Initial Tree
		root = new node();
		root->addChild(new node("Grants", 0, 0, 0));
		root->addChild(new node("Clinical Funding", 0, 0, 0));
		for (node* &i : root->getChildren()){
			i->addChild(new node("Peer Reviewed", 0, 0, 0));
			i->addChild(new node("Non-Peer Reviewed", 0, 0, 0));
			for (node* &j : i->getChildren()){
				j->addChild(new node("Industry Sponsored", 0, 0, 0));
				j->addChild(new node("Non-Industry Sponsored", 0, 0, 0));
			}
		}
		//Iterate through professors
		for (typename map<string, granProfessor*>::iterator it = professors->begin(); it != professors->end(); ++it) {
			//Sum statistics and add to tree
			vector<pair<int, float>> count(8, pair<int, float>(0, 0));
			for (int i = 0; i < it->second->getNumberOfGrants(); i++){
				int j;
				if (it->getType()->at(i) == "Grants"){
					if (it->getPeerReviewed()->at(i)){
						if (it->getIndustryGrant()->at(i)){ j = 0; }
						else                              { j = 1; }
					}
					else{
						if (it->getIndustryGrant()->at(i)){ j = 3; }
						else                              { j = 4; }
					}
				}
				else{
					if (it->getPeerReviewed()->at(i)){
						if (it->getIndustryGrant()->at(i)){ j = 5; }
						else                              { j = 6; }
					}
					else{
						if (it->getIndustryGrant()->at(i)){ j = 7; }
						else                              { j = 8; }
					}
				}
				try{
					count[j].first++;
					count[j].second += it->getFundingAmount();
				}
				catch (const std::out_of_range& oor) { std::cerr << "Out of Range error: " << oor.what() << '\n'; }
			}
			for (int i = 0; i < count.size(); i++){
				if (count[i].first != 0){
					root->getChildren()->at((i ^ 0x4) >> 2)
						->getChildren()->at((i ^ 0x2) >> 1)
						->getChildren()->at(i ^ 0x1)
						->addChild(new node(it->first, count[i].first, 0, count[i].second));
				}
			}
		}
		for (node* &i : root->getChildren()){
			int fCount = 0;
			float fFunding = 0;
			for (node* &j : i->getChildren()){
				int sCount = 0;
				float sFunding = 0;
				for (node* &k : j->getChildren()){
					int tCount = 0;
					float tFunding = 0;
					for (node* &l : k->getChildren()){
						tCount += l->getSecond();
						tFunding += l->getFourth();
					}
					k->setSecond(tCount);
					k->setFourth(tCount);
					k->organizeChildren();
					sCount += tCount;
					sFunding += tFunding;
				}
				j->setSecond(sCount);
				j->setFourth(sFunding);
				j->organizeChildren();
				fCount += sCount;
				fFunding += sFunding;
			}
			i->setSecond(fCount);
			i->setFourth(fFunding);
			i->organizeChildren();
		}
	}
	void createPresStatistics(professorMap<presProfessor>* profMap){
		//Create Initial Tree
		vector<string> presTypes;
		root = new node("Presentations", 0, 0, 0);

		for (typename map<string, presProfessor*>::iterator it = professors->begin(); it != professors->end(); ++it) {
			//Sum statistics and add to tree
			vector<int> typeCount(presTypes.size(), 0);
			//Iterator through presentations
			for (int i = 0; i < it->second->getNumberOfPres(); i++){
				//Try to find presentation in presTypes
				vector<string>::iterator ti = std::find(presTypes.begin(), presTypes.end(), it->second->getType()->at(i));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == presTypes.end()){
					presTypes.push_back(it->second->getType()->at(i));
					typeCount.push_back(1);
					root->addChild(new node(presTypes.back(), 0, 0, 0));
				}
				//Else increment count of that type
				else{
					typeCount[std::distance(presTypes.begin(), ti)]++;
				}
			}
			//Add the professor stats to the tree
			for (int i = 0; i < presTypes.size(); i++){
				root->getChildren()->at(i)->addChild(new node(it->second->getName(), typeCount[i]));
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (node* &i : root->getChildren()){
			int sCount = 0;
			for (node* &j : i->getChildren()){
				sCount += j->second;
			}
			i->setSecond(sCount);
			i->organizeChildren();
		}
		root->setSecond(fCount);
		root->organizeChildren();
	}

public:
	statisticsTree(){
		root = NULL;
	}
	statisticsTree(professorMap<T>* professors){
		statisticsTree();
		createStatistics(professors);
	}
	~statisticsTree(){ delete root; }
	node* getStatistics(){ return root; }
	void createStatistics(professorMap<T>* professors) {
		//Requires C++11 to use is_same
		//If type is of pubProfessor do
		if (std::is_same<T, pubProfessor>::value) {
			createPubStatistics(professors);
		}
		//If type is of teachProfessor do
		if (std::is_same<T, teacProfessor>::value) {
			createTeacStatistics(professors);
		}
		//If type is of granProfessor do
		if (std::is_same<T, granProfessor>::value) {
			createGranStatistics(professors);
		}
		//If type is of presProfessor do
		if (std::is_same<T, presProfessor>::value) {
			createPresStatistics(professors);
		}
	}
};
