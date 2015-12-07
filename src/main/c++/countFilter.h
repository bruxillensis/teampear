#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"
#include "filterdialog.h"
#include <QSpinBox>

using namespace std;

class countFilter : public filter{
private:
	double low;
	double high;
public:
	countFilter(filterDialog* d){
		low = d->getStartCount();
		high = d->getEndCount();
	}

	countFilter(double low, double high){
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
							if ((fourthLayer->getSecond() < low) || (fourthLayer->getSecond() > high)){
								//outside of the filter
								fourthLayer->setVisible("count",false);
								thirdLayer->setSecond(thirdLayer->getSecond() - fourthLayer->getSecond());
								secondLayer->setSecond(secondLayer->getSecond() - fourthLayer->getSecond());
								firstLayer->setSecond(firstLayer->getSecond() - fourthLayer->getSecond());
							}
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getSecond() == 0){
							thirdLayer->setVisible("count", false);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() == 0){
						secondLayer->setVisible("count", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("count", false);
				}
			}
			break;
		default:
			//non-grant
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					if ((secondLayer->getSecond() < low) || (secondLayer->getSecond() > high)){
						//outside of the filter
						secondLayer->setVisible("count", false);
						firstLayer->setSecond(firstLayer->getSecond() - secondLayer->getSecond());
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("count", false);
				}
			}
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
							if ((fourthLayer->getSecond() < low) || (fourthLayer->getSecond() > high)){
								//outside of the filter
								fourthLayer->setVisible("count", true);
								thirdLayer->setSecond(thirdLayer->getSecond() + fourthLayer->getSecond());
								secondLayer->setSecond(secondLayer->getSecond() + fourthLayer->getSecond());
								firstLayer->setSecond(firstLayer->getSecond() + fourthLayer->getSecond());
							}
						}
						if (thirdLayer->getSecond() != 0){
							thirdLayer->setVisible("count", true);
						}
					}
					if (secondLayer->getSecond() != 0){
						secondLayer->setVisible("count", true);
					}
				}
				if (firstLayer->getSecond() != 0){
					firstLayer->setVisible("count", true);
				}
			}
			break;
		default:
			//non-grant
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					if ((secondLayer->getSecond() < low) || (secondLayer->getSecond() > high)){
						//outside of the filter
						secondLayer->setVisible("count", true);
						firstLayer->setSecond(firstLayer->getSecond() + secondLayer->getSecond());
					}
				}
				if (firstLayer->getSecond() != 0){
					firstLayer->setVisible("count", true);
				}
			}
			break;
		}
	}
};
