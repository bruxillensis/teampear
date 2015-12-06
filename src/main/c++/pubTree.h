#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "professorMap.h"
#include "professor.h"
#include "statisticsTree.h"
#include "boost/variant.hpp"

using namespace std;

class pubTree : public statisticsTree{
public:
	pubTree() :statisticsTree(){}
	pubTree(professorMap* professors){
		pubTree();
		createStatistics(professors);
	}
	void createStatistics(professorMap* professors) override {
		//Create Initial Tree
		vector<string> pubTypes;
		root = new node("Publications", 0, 0, 0);

		//Iterate through professors
		for (auto& it : *professors) {
			//Sum statistics and add to tree
			vector<int> typeCount(pubTypes.size(),0);
			vector<vector<string>> titles(pubTypes.size(), vector<string>());
			//Iterator through publications
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				//Try to find publication in pubTypes
				vector<string>::iterator ti = std::find(pubTypes.begin(), pubTypes.end(), boost::get<string>
					(it.second->getField(1)->at(i)));
				//If not found, add new entry to pubTypes, tree and count
				if (ti == pubTypes.end()){
					boost::get<string>(it.second->getField(1)->at(i));
					pubTypes.push_back(boost::get<string>(it.second->getField(1)->at(i)));
					typeCount.push_back(1);
					titles.push_back(vector<string>(1, boost::get<string>(it.second->getField(4)->at(i))));
					root->addChild(new node(pubTypes.back(), 0, 0, 0));
				}
				//Else increment count of that type
				else{
					typeCount[std::distance(pubTypes.begin(), ti)]++;
					titles[std::distance(pubTypes.begin(), ti)].push_back(boost::get<string>(it.second->getField(4)->at(i)));
				}
			}
			//Add the professor stats to the tree
			for (int i = 0; i < root->getChildren()->size(); i++){
				int j = std::distance(pubTypes.begin(),
					std::find(pubTypes.begin(), pubTypes.end(), root->getChildren()->at(i)->getFirst()));
				if (typeCount[j]){
					node* prof = new node(it.first, typeCount[j], 0, 0);
					for (auto& k : titles[j])
						prof->addChild(new node(k, 0, 0, 0));
					root->getChildren()->at(i)->addChild(prof);
				}
			}
		}
		//For non-leaf nodes, iterate through tree and count up stats to create totals for inner leaves
		int fCount = 0;
		for (auto &i : *root->getChildren()){
			int sCount = 0;
			for (auto &j : *(i->getChildren())){
				sCount += j->getSecond();
			}
			i->setSecond(sCount);
			fCount += sCount;
		}
		root->setSecond(fCount);
	}
	void addFilter() override {}
	void removeFilter() override {}
};
