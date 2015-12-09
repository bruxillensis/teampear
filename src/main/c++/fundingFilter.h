#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "filterdialog.h"

using namespace std;

class fundingFilter : public filter{
private:
	double low;
	double high;
	professorMap::profType type;
	node* root;
public:
	fundingFilter(filterDialog* d){
		low = d->getStartAmount();
		high = d->getEndAmount();
	}

	fundingFilter(double low, double high){
		this->low = low;
		this->high = high;
	}


	void applyFilter(node* rootX, professorMap::profType typeX){
		this->root = rootX;
		this->type = typeX;
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

								//update funding numbers
								thirdLayer->setFourth(thirdLayer->getFourth() - fourthLayer->getFourth());
								secondLayer->setFourth(secondLayer->getFourth() - fourthLayer->getFourth());
								firstLayer->setFourth(firstLayer->getFourth() - fourthLayer->getFourth());
								root->setFourth(root->getFourth() - fourthLayer->getFourth());

								//update count numbers
								thirdLayer->setSecond(thirdLayer->getSecond() - fourthLayer->getSecond());
								secondLayer->setSecond(secondLayer->getSecond() - fourthLayer->getSecond());
								firstLayer->setSecond(firstLayer->getSecond() - fourthLayer->getSecond());
								root->setSecond(root->getSecond() - fourthLayer->getSecond());
							}
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getSecond() == 0){
							thirdLayer->setVisible("funding", false);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() == 0){
						secondLayer->setVisible("funding", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("funding", false);
				}
			}
			break;
		default:
			//non-grant
			break;
		}
	}

	void removeFilter() override{
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

								//update funding numbers
								thirdLayer->setFourth(thirdLayer->getFourth() + fourthLayer->getFourth());
								secondLayer->setFourth(secondLayer->getFourth() + fourthLayer->getFourth());
								firstLayer->setFourth(firstLayer->getFourth() + fourthLayer->getFourth());
								root->setFourth(root->getFourth() + fourthLayer->getFourth());

								//update count numbers
								thirdLayer->setSecond(thirdLayer->getSecond() + fourthLayer->getSecond());
								secondLayer->setSecond(secondLayer->getSecond() + fourthLayer->getSecond());
								firstLayer->setSecond(firstLayer->getSecond() + fourthLayer->getSecond());
								root->setSecond(root->getSecond() + fourthLayer->getSecond());
							}
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getSecond() != 0){
							thirdLayer->setVisible("funding", true);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() != 0){
						secondLayer->setVisible("funding", true);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() != 0){
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