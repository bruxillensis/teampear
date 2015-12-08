#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"
#include "createProfessor.h"
#include "professor.h"
#include "filterdialog.h"
#include <QSpinBox>

using namespace std;

class hourFilter : public filter{
private:
	float low;
	float high;
public:
	hourFilter(filterDialog* d){
		low = d->getStartHours();
		high = d->getEndHours();
	}

	hourFilter(float low, float high){
		this->low = low;
		this->high = high;
	}


	void applyFilter(node* root, professorMap* map){
		//only for teaching
		//traverse the tree
		for (auto &firstLayer : *root->getChildren()){
			for (auto &secondLayer : *firstLayer->getChildren()){
				const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* hours = map->getProfessor(secondLayer->getFirst())->getField(7);
				if ((boost::get<float>(hours->at(0)) < low) || (boost::get<float>(hours->at(0)) > high)){
					//outside of the filter
					secondLayer->setVisible("hours", false);
					firstLayer->setSecond(firstLayer->getSecond() - secondLayer->getSecond());
					root->setSecond(root->getSecond() - secondLayer->getSecond());					
				}
			}
			//parent node checks if the children are visible
			if (firstLayer->getSecond() == 0){
				firstLayer->setVisible("hours", false);
			}
		}
	}

	void removeFilter(node* root, professorMap* map){
		//only for teaching
		//traverse the tree
		for (auto &firstLayer : *root->getChildren()){
			for (auto &secondLayer : *firstLayer->getChildren()){
				const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* hours = map->getProfessor(secondLayer->getFirst())->getField(7);
				if ((boost::get<float>(hours->at(0)) < low) || (boost::get<float>(hours->at(0)) > high)){
					//outside of the filter
					secondLayer->setVisible("hours", true);
					firstLayer->setSecond(firstLayer->getSecond() + secondLayer->getSecond());
					root->setSecond(root->getSecond() + secondLayer->getSecond());
				}
			}
			//parent node checks if the children are visible
			if (firstLayer->getSecond() == 0){
				firstLayer->setVisible("hours", true);
			}
		}
	}
};