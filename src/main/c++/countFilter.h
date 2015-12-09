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
	professorMap::profType type;
	node* root;
public:
	countFilter(filterDialog* d){
		low = d->getStartCount();
		high = d->getEndCount();
	}

	countFilter(double low, double high){
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
							if ((fourthLayer->getSecond() < low) || (fourthLayer->getSecond() > high)){
								//outside of the filter
								if (fourthLayer->getVisible() == true){
									//update funding numbers
									thirdLayer->setFourth(thirdLayer->getFourth() - fourthLayer->getFourth());
									secondLayer->setFourth(secondLayer->getFourth() - fourthLayer->getFourth());
									firstLayer->setFourth(firstLayer->getFourth() - fourthLayer->getFourth());
									root->setFourth(root->getFourth() - fourthLayer->getFourth());
									
									//update count number
									thirdLayer->setSecond(thirdLayer->getSecond() - fourthLayer->getSecond());
									secondLayer->setSecond(secondLayer->getSecond() - fourthLayer->getSecond());
									firstLayer->setSecond(firstLayer->getSecond() - fourthLayer->getSecond());
									root->setSecond(root->getSecond() - fourthLayer->getSecond());
								}
								fourthLayer->setVisible("count", false);
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

						if (secondLayer->getVisible() == true){
							if (type == professorMap::profType::Teaching){
								//update hours numbers
								firstLayer->setFourth(firstLayer->getFourth() - secondLayer->getFourth());
								root->setFourth(root->getFourth() - secondLayer->getFourth());
							}

							//update count numbers
							firstLayer->setSecond(firstLayer->getSecond() - secondLayer->getSecond());
							root->setSecond(root->getSecond() - secondLayer->getSecond());
						}
						secondLayer->setVisible("count", false);
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

	void removeFilter() override{
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

								if (fourthLayer->getVisible() == true){
									//update funding numbers
									thirdLayer->setFourth(thirdLayer->getFourth() + fourthLayer->getFourth());
									secondLayer->setFourth(secondLayer->getFourth() + fourthLayer->getFourth());
									firstLayer->setFourth(firstLayer->getFourth() + fourthLayer->getFourth());
									root->setFourth(root->getFourth() + fourthLayer->getFourth());

									//update count number
									thirdLayer->setSecond(thirdLayer->getSecond() + fourthLayer->getSecond());
									secondLayer->setSecond(secondLayer->getSecond() + fourthLayer->getSecond());
									firstLayer->setSecond(firstLayer->getSecond() + fourthLayer->getSecond());
									root->setSecond(root->getSecond() + fourthLayer->getSecond());
								}
							}
						}
							thirdLayer->setVisible("count", true);
					}
						secondLayer->setVisible("count", true);
				}
					firstLayer->setVisible("count", true);
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
						
						if (secondLayer->getVisible() == true){
							if (type == professorMap::profType::Teaching){
								//update hours numbers
								firstLayer->setFourth(firstLayer->getFourth() + secondLayer->getFourth());
								root->setFourth(root->getFourth() + secondLayer->getFourth());
							}

							//update count numbers
							firstLayer->setSecond(firstLayer->getSecond() + secondLayer->getSecond());
							root->setSecond(root->getSecond() + secondLayer->getSecond());
						}
					}
				}
				firstLayer->setVisible("count", true);
				
			}
			break;
		}
	}
};
