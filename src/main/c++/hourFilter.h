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
	professorMap::profType type;
	node* root;
public:
	hourFilter(filterDialog* d){
		low = d->getStartHours();
		high = d->getEndHours();
	}

	hourFilter(float low, float high){
		this->low = low;
		this->high = high;
	}


	void applyFilter(node* rootX, professorMap::profType typeX){
		this->root = rootX;
		this->type = typeX;
		switch (type){
		case professorMap::profType::Teaching:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					if ((secondLayer->getFourth() < low) || (secondLayer->getFourth() > high)){
						//outside of the filter
						secondLayer->setVisible("hours", false);

						//update hours numbers
						firstLayer->setFourth(firstLayer->getFourth() - secondLayer->getFourth());
						root->setFourth(root->getFourth() - secondLayer->getFourth());

						//update count numbers
						firstLayer->setSecond(firstLayer->getSecond() - secondLayer->getSecond());
						root->setSecond(root->getSecond() - secondLayer->getSecond());
					}
				}
			
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("hours", false);
				}
			}
			break;
		default:
			//non-teaching
			break;
		}
	}

	void removeFilter() override{
		switch (type){
		case professorMap::profType::Teaching:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					if ((secondLayer->getFourth() < low) || (secondLayer->getFourth() > high)){
						//outside of the filter
						secondLayer->setVisible("hours", true);

						//update hours numbers
						firstLayer->setFourth(firstLayer->getFourth() + secondLayer->getFourth());
						root->setFourth(root->getFourth() + secondLayer->getFourth());

						//update count numbers
						firstLayer->setSecond(firstLayer->getSecond() + secondLayer->getSecond());
						root->setSecond(root->getSecond() + secondLayer->getSecond());
					}
				}

				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() != 0){
					firstLayer->setVisible("hours", true);
				}
			}
			break;
		default:
			//non-teaching
			break;
		}
	}
};