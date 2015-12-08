#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"

using namespace std;

class fundingFilter : public filter{
private:
	double low;
	double high;
public:
	fundingFilter(){
		low = 0;
		high = 0;
	}

	fundingFilter(double low, double high){
		this->low = low;
		this->high = high;
	}


	void applyFilter(node* root, professorMap::profType type){
		switch (type){
		case professorMap::profType::GrantClinical:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					for (auto &thirdLayer : *secondLayer->getChildren()){
						for (auto &fourthLayer : *thirdLayer->getChildren()){
							if ((fourthLayer->getFourth() < low) || (fourthLayer->getFourth() > high)){
								//outside of the filter
								fourthLayer->setVisible("funding", false);
								thirdLayer->setFourth(thirdLayer->getFourth - fourthLayer->getFourth());
								secondLayer->setFourth(secondLayer->getFourth - fourthLayer->getFourth());
								firstLayer->setFourth(firstLayer->getFourth - fourthLayer->getFourth());
							}
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getFourth() == 0){
							thirdLayer->setVisible("funding", false);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getFourth() == 0){
						secondLayer->setVisible("funding", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getFourth() == 0){
					firstLayer->setVisible("funding", false);
				}
			}
			break;
		default:
			//non-grant
			break;
		}
	}

	void removeFilter(node* root, professorMap::profType type){
		switch (type){
		case professorMap::profType::GrantClinical:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					for (auto &thirdLayer : *secondLayer->getChildren()){
						for (auto &fourthLayer : *thirdLayer->getChildren()){
							if ((fourthLayer->getFourth() < low) || (fourthLayer->getFourth() > high)){
								//outside of the filter
								fourthLayer->setVisible("funding", true);
								thirdLayer->setFourth(thirdLayer->getFourth + fourthLayer->getFourth());
								secondLayer->setFourth(secondLayer->getFourth + fourthLayer->getFourth());
								firstLayer->setFourth(firstLayer->getFourth + fourthLayer->getFourth());
							}
						}
						if (thirdLayer->getFourth() != 0){
							thirdLayer->setVisible("funding", true);
						}
					}
					if (secondLayer->getFourth() != 0){
						secondLayer->setVisible("funding", true);
					}
				}
				if (firstLayer->getFourth() != 0){
					firstLayer->setVisible("funding", true);
				}
			}
			break;
		default:
			//non-grant
			break;
		}
	}
};