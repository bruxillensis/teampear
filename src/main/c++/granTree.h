#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "professorMap.h"
#include "statisticsTree.h"
#include "boost/variant.hpp"

using namespace std;

class granTree : public statisticsTree{
public:
	granTree():statisticsTree(){}
	granTree(professorMap* professors){
		granTree();
		createStatistics(professors);
	}
	void createStatistics(professorMap* professors) override {
		//Create Initial Tree
		root = new node("Grants and Clinical Funding", 0, 0, 0);
		root->addChild(new node("Clinical Funding", 0, 0, 0));
		root->addChild(new node("Grants", 0, 0, 0));
		for (auto &i : *root->getChildren()){
			i->addChild(new node("Non-Peer Reviewed", 0, 0, 0));
			i->addChild(new node("Peer Reviewed", 0, 0, 0));
			for (auto &j : *i->getChildren()){
				j->addChild(new node("Industry Sponsored", 0, 0, 0));
				j->addChild(new node("Non-Industry Sponsored", 0, 0, 0));
			}
		}

		//Iterate through professors
		for (auto& it : *professors) {
			//Sum statistics and add to tree
			vector<pair<int, float>> count(8, pair<int, float>(0, 0));
			vector<vector<string>> titles(8, vector<string>());
			vector<vector<float>> amounts(8, vector<float>());
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				int j;
				//Grants
				if (boost::get<string>(it.second->getField(2)->at(i)) == "Clinical Trials"){
					if (!boost::get<bool>(it.second->getField(4)->at(i))){
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 0; }
						else												{ j = 1; }
					}
					else{
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 2; }
						else												{ j = 3; }
					}
				}
				//Clinical funding
				else{
					if (!boost::get<bool>(it.second->getField(4)->at(i))){
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 4; }
						else												{ j = 5; }
					}
					else{
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 6; }
						else												{ j = 7; }
					}
				}
				try{
					count[j].first++;
					count[j].second += boost::get<float>(it.second->getField(10)->at(i));
					titles[j].push_back(boost::get<string>(it.second->getField(7)->at(i)));
					amounts[j].push_back(boost::get<float>(it.second->getField(10)->at(i)));
				}
				catch (const std::out_of_range& oor) { std::cerr << "Out of Range error: " << oor.what() << '\n'; }
			}
			for (int i = 0; i < count.size(); i++){
				if (count[i].first != 0){
					node* prof = new node(it.first, count[i].first, 0, count[i].second);
					for (int j = 0; j < titles[i].size(); j++)
						prof->addChild(new node(titles[i][j], 1, 0, amounts[i][j]));
					root->getChildren()->at((i & 0x4) >> 2)
						->getChildren()->at((i & 0x2) >> 1)
						->getChildren()->at(i & 0x1)
						->addChild(prof);
				}
			}
		}
		this->getTotals();
	}
	void addFilter() override {}
	void removeFilter() override {}
};
