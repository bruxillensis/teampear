#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "professorMap.h"
#include "professor.h"
#include "statisticsTree.h"
#include "boost/variant.hpp"

using namespace std;

class teacTree : public statisticsTree{
public:
	teacTree() :statisticsTree(){}
	teacTree(professorMap* professors){
		teacTree();
		createStatistics(professors);
	}
	void createStatistics(professorMap* professors) override {
		//Create Initial Tree
		vector<string> teachTypes;
		root = new node("Programs", 0, 0, 0);

		for (auto& it : *professors) {
			//Sum statistics and add to tree
			vector<int> typeCount(teachTypes.size(), 0);
			//Iterator through class entries
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				//Try to find teaching type in teachTypes
				vector<string>::iterator ti = std::find(teachTypes.begin(), teachTypes.end(), boost::get<string>
					(it.second->getField(2)->at(i)));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == teachTypes.end()){
					teachTypes.push_back(boost::get<string>(it.second->getField(2)->at(i)));
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
				root->getChildren()->at(i)->addChild(new node(it.second->getName(), typeCount[i], 0, 0));
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (auto &i : *root->getChildren()){
			int sCount = 0;
			for (auto &j : *i->getChildren()){
				sCount += j->getSecond();
			}
			i->setSecond(sCount);
		}
		root->setSecond(fCount);
	}
	void addFilter() override {}
	void removeFilter() override {}
};
