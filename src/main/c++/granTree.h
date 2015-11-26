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
		root = new node("Grants and Clinicl Funding", 0, 0, 0);
		root->addChild(new node("Grants", 0, 0, 0));
		root->addChild(new node("Clinical Funding", 0, 0, 0));
		for (auto &i : *root->getChildren()){
			i->addChild(new node("Peer Reviewed", 0, 0, 0));
			i->addChild(new node("Non-Peer Reviewed", 0, 0, 0));
			for (auto &j : *i->getChildren()){
				j->addChild(new node("Industry Sponsored", 0, 0, 0));
				j->addChild(new node("Non-Industry Sponsored", 0, 0, 0));
			}
		}

		//Iterate through professors
		for (auto& it : *professors) {
			//Sum statistics and add to tree
			//vector<pair<int, float>> count(8, pair<int, float>(0, 0));
			vector<pair<int, float>> count;
			for (int i = 0; i < 8; i++){
				count.push_back(pair<int, float>(0, 0));
			}
			
			
			
			for (int i = 0; i < it.second->getNumberOfEntries(); i++){
				int j;
				if (boost::get<string>(it.second->getField(0)->at(i)) == "Grants"){
					if (boost::get<bool>(it.second->getField(4)->at(i))){
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 0; }
						else												{ j = 1; }
					}
					else{
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 3; }
						else												{ j = 4; }
					}
				}
				else{
					if (boost::get<bool>(it.second->getField(4)->at(i))){
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 5; }
						else												{ j = 6; }
					}
					else{
						if (boost::get<bool>(it.second->getField(5)->at(i))){ j = 7; }
						else												{ j = 8; }
					}
				}
				try{
					count[j].first++;
					count[j].second += boost::get<float>(it.second->getField(10)->at(i));
				}
				catch (const std::out_of_range& oor) { std::cerr << "Out of Range error: " << oor.what() << '\n'; }
			}
			for (int i = 0; i < count.size(); i++){
				if (count[i].first != 0){
					root->getChildren()->at((i ^ 0x4) >> 2)
						->getChildren()->at((i ^ 0x2) >> 1)
						->getChildren()->at(i ^ 0x1)
						->addChild(new node(it.first, count[i].first, 0, count[i].second));
				}
			}
		}
		for (auto &i : *root->getChildren()){
			int fCount = 0;
			float fFunding = 0;
			for (auto &j : *i->getChildren()){
				int sCount = 0;
				float sFunding = 0;
				for (auto &k : *j->getChildren()){
					int tCount = 0;
					float tFunding = 0;
					for (auto &l : *k->getChildren()){
						tCount += l->getSecond();
						tFunding += l->getFourth();
					}
					k->setSecond(tCount);
					k->setFourth(tCount);
					sCount += tCount;
					sFunding += tFunding;
				}
				j->setSecond(sCount);
				j->setFourth(sFunding);
				fCount += sCount;
				fFunding += sFunding;
			}
			i->setSecond(fCount);
			i->setFourth(fFunding);
		}
	}
	void addFilter() override {}
	void removeFilter() override {}
};
