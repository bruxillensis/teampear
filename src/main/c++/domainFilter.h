#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"
#include "filterdialog.h"
#include <QSpinBox>
#include <QString>

using namespace std;

class domainFilter : public filter{
private:
	string domain;
	node* root;
	professorMap::profType type;
	professorMap* map;
public:
	domainFilter(filterDialog* d){
		domain = (d->getDomain()).toStdString();
	}

	void applyFilter(node* rootX, professorMap::profType typeX, professorMap* mapX){
		this->root = rootX;
		this->type = typeX;
		this->map = mapX;
		switch (type){
		case professorMap::profType::GrantClinical:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					for (auto &thirdLayer : *secondLayer->getChildren()){
						for (auto &fourthLayer : *thirdLayer->getChildren()){
							string nodeDomain = map->getProfessor(fourthLayer->getFirst())->getDomain();
							if (nodeDomain.compare(domain) != 0){
								//outside of the filter

								if (fourthLayer->getVisible() == true){
									//update numbers
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

								fourthLayer->setVisible("domain", false);
							}
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getSecond() == 0){
							thirdLayer->setVisible("domain", false);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() == 0){
						secondLayer->setVisible("domain", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("domain", false);
				}
			}
			break;
		default:
			//non-grant
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					string nodeDomain = map->getProfessor(secondLayer->getFirst())->getDomain();
					if (nodeDomain.compare(domain) != 0){
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
						secondLayer->setVisible("domain", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("domain", false);
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
							string nodeDomain = map->getProfessor(fourthLayer->getFirst())->getDomain();
							if (nodeDomain.compare(domain) != 0){
								//outside of the filter
								fourthLayer->setVisible("domain", true);

								//update numbers
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
							thirdLayer->setVisible("domain", true);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() != 0){
						secondLayer->setVisible("domain", true);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() != 0){
					firstLayer->setVisible("domain", true);
				}
			}
			break;
		default:
			//non-grant
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					string nodeDomain = map->getProfessor(secondLayer->getFirst())->getDomain();
					if (nodeDomain.compare(domain) != 0){
						//outside of the filter
						secondLayer->setVisible("domain", true);

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
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() != 0){
					firstLayer->setVisible("domain", true);
				}
			}
			break;
		}
	}
};
