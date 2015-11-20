#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "professorMap.h"
#include "statisticsTree.h"

using namespace std;

class presTree : public statisticsTree{
public:
	presTree() :statisticsTree(){}
	presTree(professorMap* professors){
		statisticsTree();
		createStatistics(professors);
	}
	void createStatistics(professorMap* professors) override {
		//Create Initial Tree
		vector<string> presTypes;
		root = new node("Presentations", 0, 0, 0);

		for (auto& it : *professors) {
			//Sum statistics and add to tree
			vector<int> typeCount(presTypes.size(), 0);
			//Iterator through presentations
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				//Try to find presentation in presTypes
				vector<string>::iterator ti = std::find(presTypes.begin(), presTypes.end(), boost::get<string>
					(it.second->getField(1)->at(i)));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == presTypes.end()){
					presTypes.push_back(boost::get<string>(it.second->getField(1)->at(i)));
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
				root->getChildren()->at(i)->addChild(new node(it.second->getName(), typeCount[i], 0, 0));
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (node* &i : *root->getChildren()){
			int sCount = 0;
			for (node* &j : *i->getChildren()){
				sCount += j->getSecond();
			}
			i->setSecond(sCount);
		}
		root->setSecond(fCount);
	}
	void addFilter() override {}
	void removeFilter() override {}
};
