#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"
#include "createProfessor.h"
#include "professor.h"
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;

class dateFilter : public filter{
private:
	boost::gregorian::date low;
	boost::gregorian::date high;
public:
	dateFilter(){
	}

	dateFilter(boost::gregorian::date low, boost::gregorian::date high){
		this->low = low;
		this->high = high;
	}


	void applyFilter(node* root, professorMap::profType type, professorMap* map){
		switch (type){
		case professorMap::profType::Publication:
		case professorMap::profType::Presentation:
			//only for teaching
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* date;
					if (type = professorMap::profType::Publication)
						date = map->getProfessor(secondLayer->getFirst())->getField(6);
					else
						date = map->getProfessor(secondLayer->getFirst())->getField(3);

					if ((boost::get<boost::gregorian::date>(date->at(0)) < low) || (boost::get<boost::gregorian::date>(date->at(0)) > high)){
						//outside of the filter
						secondLayer->setVisible("false", true);
						firstLayer->setSecond(firstLayer->getSecond - secondLayer->getSecond());
					}
				}
				//parent node checks if the children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("false", true);
				}
			}
			break;

		case professorMap::profType::GrantClinical:
		case professorMap::profType::Teaching:
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* startDate;
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* endDate;
					startDate = map->getProfessor(secondLayer->getFirst())->getField(0);
					endDate = map->getProfessor(secondLayer->getFirst())->getField(1);

					if ((boost::get<boost::gregorian::date>(startDate->at(0)) < low) || (boost::get<boost::gregorian::date>(startDate->at(0)) > high) || (boost::get<boost::gregorian::date>(endDate->at(0)) < low) || (boost::get<boost::gregorian::date>(endDate->at(0)) > high)){
						//outside of the filter
						secondLayer->setVisible("false", true);
						firstLayer->setSecond(firstLayer->getSecond - secondLayer->getSecond());
					}
				}
				//parent node checks if the children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("false", true);
				}
			}
			break;
		}
	}

	void removeFilter(node* root){

	}
};