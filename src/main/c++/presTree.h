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
			vector<vector<string>> titles(presTypes.size(), vector<string>());
			//Iterator through presentations
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				//Try to find presentation in presTypes
				vector<string>::iterator ti = std::find(presTypes.begin(), presTypes.end(), boost::get<string>
					(it.second->getField(1)->at(i)));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == presTypes.end()){
					presTypes.push_back(boost::get<string>(it.second->getField(1)->at(i)));
					typeCount.push_back(1);
					titles.push_back(vector<string>(1, boost::get<string>(it.second->getField(2)->at(i))));
					root->addChild(new node(presTypes.back(), 0, 0, 0));
				}
				//Else increment count of that type
				else{
					typeCount[std::distance(presTypes.begin(), ti)]++;
					titles[std::distance(presTypes.begin(), ti)].push_back(boost::get<string>(it.second->getField(2)->at(i)));
				}
			}
			//Add the professor stats to the tree
			for (int i = 0; i < presTypes.size(); i++){
				int j = std::distance(presTypes.begin(),
					std::find(presTypes.begin(), presTypes.end(), root->getChildren()->at(i)->getFirst()));
				if (typeCount[j]){
					node* prof = new node(it.first, typeCount[j], 0, 0);
					for (auto& k : titles[j])
						prof->addChild(new node(k, 1, 0, 0));
					root->getChildren()->at(i)->addChild(prof);
				}
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		this->getTotals();
	}
	void addFilter() override {}
	void removeFilter() override {}
};
