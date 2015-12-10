#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "filter.h"
#include "professorMap.h"
#include "createProfessor.h"
#include "professor.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "filterdialog.h"
#include <QDate>

using namespace std;

class dateFilter : public filter{
private:
	string low;
	string high;
	node* root;
	professorMap::profType type;
	professorMap* map;
public:
	dateFilter(filterDialog* d){
		low = to_iso_string(boost::gregorian::date(d->getStartDate().year(), d->getStartDate().month(), d->getStartDate().day()));
		high = to_iso_string(boost::gregorian::date(d->getEndDate().year(), d->getEndDate().month(), d->getEndDate().day()));
	}

	void applyFilter(node* rootX, professorMap::profType typeX, professorMap* mapX){
		this->root = rootX;
		this->type = typeX;
		this->map = mapX;
		switch (type){
		case professorMap::profType::Presentation:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* date;
					date = map->getProfessor(secondLayer->getFirst())->getField(3);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* type;
					type = map->getProfessor(secondLayer->getFirst())->getField(0);

					//get date from gregorian date
					string dateString;
					int outsideCount = 0;
					int inProgram = 0;
					for (int i = 0; i < date->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(type->at(i)).compare(firstLayer->getFirst()) == 0){
							inProgram++;
							dateString = to_iso_string(boost::get<boost::gregorian::date>(date->at(i)));
							if (((dateString < low) || (dateString > high))){
								//outside the filter
								outsideCount++;
								if (secondLayer->getVisible() == true){
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() - 1);
									firstLayer->setSecond(firstLayer->getSecond() - 1);
									root->setSecond(root->getSecond() - 1);
								}
							}
						}

					}
					if (outsideCount == inProgram)
						secondLayer->setVisible("date", false);
				}
				//parent node checks if the children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("date", false);
				}
			}
			break;
		case professorMap::profType::Publication:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* date;
					date = map->getProfessor(secondLayer->getFirst())->getField(2);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* type;
					type = map->getProfessor(secondLayer->getFirst())->getField(1);

					//get date from gregorian date
					string dateString;
					int outsideCount = 0;
					int inProgram = 0;
					for (int i = 0; i < date->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(type->at(i)).compare(firstLayer->getFirst()) == 0){
							inProgram++;
							dateString = to_iso_string(boost::get<boost::gregorian::date>(date->at(i)));
							if (((dateString < low) || (dateString > high))){
								//outside the filter
								outsideCount++;
								if (secondLayer->getVisible() == true){
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() - 1);
									firstLayer->setSecond(firstLayer->getSecond() - 1);
									root->setSecond(root->getSecond() - 1);
								}
							}
						}
					}
					if (outsideCount == inProgram)
						secondLayer->setVisible("date", false);
				}
				//parent node checks if the children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("date", false);
				}
			}
			break;

		case professorMap::profType::GrantClinical:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					for (auto &thirdLayer : *secondLayer->getChildren()){
						for (auto &fourthLayer : *thirdLayer->getChildren()){
							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* startDate;
							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* endDate;
							startDate = map->getProfessor(fourthLayer->getFirst())->getField(0);
							endDate = map->getProfessor(fourthLayer->getFirst())->getField(1);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* grant;
							grant = map->getProfessor(fourthLayer->getFirst())->getField(2);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* peer;
							peer = map->getProfessor(fourthLayer->getFirst())->getField(4);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* industry;
							industry = map->getProfessor(fourthLayer->getFirst())->getField(5);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* funding;
							funding = map->getProfessor(fourthLayer->getFirst())->getField(10);

							//get date from gregorian date
							string startDateString;
							string endDateString;
							int outsideCount = 0; 
							int inProgram = 0;
							for (int i = 0; i < startDate->size(); i++){
								//check the type to see if it's the same
								if ((boost::get<string>(grant->at(i)).find(firstLayer->getFirst().substr(0,5)) != string::npos)){
									//then check to see if peer or non-peer is the same
									bool check = boost::get<bool>(peer->at(i));
									if ((check && (secondLayer->getFirst().find("Peer") == 0)) || (!check && (secondLayer->getFirst().find("Peer") != 0))){
										//then check to see if industry or non-industry sponsored is the same
										check = boost::get<bool>(industry->at(i));
										if ((check && (thirdLayer->getFirst().find("Industry") == 0)) || (!check && (thirdLayer->getFirst().find("Industry") != 0))){
											inProgram++;
											startDateString = to_iso_string(boost::get<boost::gregorian::date>(startDate->at(i)));
											endDateString = to_iso_string(boost::get<boost::gregorian::date>(endDate->at(i)));
											if (((startDateString < low) || (startDateString > high)) && ((endDateString < low) || (endDateString > high))){
												//outside the filter
												outsideCount++;
												/*
												for (auto &fifthLayer : *fourthLayer->getChildren()){
													if (fifthLayer->getFourth() == boost::get<float>(funding->at(i)))
														fifthLayer->setVisible("date", false);
												}
												if (fourthLayer->getVisible() == true){
													//update hours
													fourthLayer->setFourth(fourthLayer->getFourth() - boost::get<float>(funding->at(i)));
													thirdLayer->setFourth(thirdLayer->getFourth() - boost::get<float>(funding->at(i)));
													secondLayer->setFourth(secondLayer->getFourth() - boost::get<float>(funding->at(i)));
													firstLayer->setFourth(firstLayer->getFourth() - boost::get<float>(funding->at(i)));
													root->setFourth(root->getFourth() - boost::get<float>(funding->at(i)));
													
													//update count numbers
													fourthLayer->setSecond(fourthLayer->getSecond() - 1);
													thirdLayer->setSecond(thirdLayer->getSecond() - 1);
													secondLayer->setSecond(secondLayer->getSecond() - 1);
													firstLayer->setSecond(firstLayer->getSecond() - 1);
													root->setSecond(root->getSecond() - 1);
												}*/
												for (auto &fifthLayer : *fourthLayer->getChildren()){
													if (fifthLayer->getFourth() == boost::get<float>(funding->at(i)))
														fifthLayer->setVisible("date", false);
												}
												if (fourthLayer->getVisible() == true){
													//update hours
													fourthLayer->setFourth(fourthLayer->getFourth() - boost::get<float>(funding->at(i)));
													thirdLayer->setFourth(thirdLayer->getFourth() - boost::get<float>(funding->at(i)));
													secondLayer->setFourth(secondLayer->getFourth() - boost::get<float>(funding->at(i)));
													firstLayer->setFourth(firstLayer->getFourth() - boost::get<float>(funding->at(i)));
													root->setFourth(root->getFourth() - boost::get<float>(funding->at(i)));

													//update count numbers
													fourthLayer->setSecond(fourthLayer->getSecond() - 1);
													thirdLayer->setSecond(thirdLayer->getSecond() - 1);
													secondLayer->setSecond(secondLayer->getSecond() - 1);
													firstLayer->setSecond(firstLayer->getSecond() - 1);
													root->setSecond(root->getSecond() - 1);
												}
											}
										}
									}
								}
							}
							if (outsideCount == inProgram)
								fourthLayer->setVisible("date", false);
						}
						//checks to see if any of the children are visible, if the count = 0, that means no children are visible
						if (thirdLayer->getSecond() == 0){
							thirdLayer->setVisible("date", false);
						}
					}
					//checks to see if any of the children are visible, if the count = 0, that means no children are visible
					if (secondLayer->getSecond() == 0){
						secondLayer->setVisible("date", false);
					}
				}
				//checks to see if any of the children are visible, if the count = 0, that means no children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("date", false);
				}
			}
			break;

		case professorMap::profType::Teaching:
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* startDate;
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* endDate;
					startDate = map->getProfessor(secondLayer->getFirst())->getField(0);
					endDate = map->getProfessor(secondLayer->getFirst())->getField(1);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* program;
					program = map->getProfessor(secondLayer->getFirst())->getField(2);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* profHours;
					profHours = map->getProfessor(secondLayer->getFirst())->getField(7);

					//get date from gregorian date
					string startDateString;
					string endDateString;
					int outsideCount = 0;
					int inProgram = 0;
					for (int i = 0; i < startDate->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(program->at(i)).compare(firstLayer->getFirst()) == 0){
							inProgram++;
							startDateString = to_iso_string(boost::get<boost::gregorian::date>(startDate->at(i)));
							endDateString = to_iso_string(boost::get<boost::gregorian::date>(endDate->at(i)));
							if (((startDateString < low) || (startDateString > high)) && ((endDateString < low) || (endDateString > high))){
								//outside the filter
								outsideCount++;
								if (secondLayer->getVisible() == true){
									//update hours
									secondLayer->setFourth(secondLayer->getFourth() - boost::get<float>(profHours->at(i)));
									firstLayer->setFourth(firstLayer->getFourth() - boost::get<float>(profHours->at(i)));
									root->setFourth(root->getFourth() - boost::get<float>(profHours->at(i)));
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() - 1);
									firstLayer->setSecond(firstLayer->getSecond() - 1);
									root->setSecond(root->getSecond() - 1);
								}
							}
						}
					}
					if (outsideCount == inProgram)
						secondLayer->setVisible("date", false);
				}
				//parent node checks if the children are visible
				if (firstLayer->getSecond() == 0){
					firstLayer->setVisible("date", false);
				}
			}
			break;
		}
	}

	void removeFilter() override{
		switch (type){
		case professorMap::profType::Presentation:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* date;
					date = map->getProfessor(secondLayer->getFirst())->getField(3);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* type;
					type = map->getProfessor(secondLayer->getFirst())->getField(0);

					//get date from gregorian date
					string dateString;
					for (int i = 0; i < date->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(type->at(i)).compare(firstLayer->getFirst()) == 0){
							dateString = to_iso_string(boost::get<boost::gregorian::date>(date->at(i)));
							if (((dateString < low) || (dateString > high))){
								//outside the filter
								secondLayer->setVisible("date", true);
								if (secondLayer->getVisible() == true){
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() + 1);
									firstLayer->setSecond(firstLayer->getSecond() + 1);
									root->setSecond(root->getSecond() + 1);
								}
							}
						}
					}
				}
				firstLayer->setVisible("date", true);
			}
			break;
		case professorMap::profType::Publication:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* date;
					date = map->getProfessor(secondLayer->getFirst())->getField(2);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* type;
					type = map->getProfessor(secondLayer->getFirst())->getField(1);

					//get date from gregorian date
					string dateString;
					for (int i = 0; i < date->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(type->at(i)).compare(firstLayer->getFirst()) == 0){
							dateString = to_iso_string(boost::get<boost::gregorian::date>(date->at(i)));
							if (((dateString < low) || (dateString > high))){
								//outside the filter
								secondLayer->setVisible("date", true);
								if (secondLayer->getVisible() == true){
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() + 1);
									firstLayer->setSecond(firstLayer->getSecond() + 1);
									root->setSecond(root->getSecond() + 1);
								}
							}
						}
					}
				}
				firstLayer->setVisible("date", true);
			}
			break;

		case professorMap::profType::GrantClinical:
			//traverse the tree
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					for (auto &thirdLayer : *secondLayer->getChildren()){
						for (auto &fourthLayer : *thirdLayer->getChildren()){
							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* startDate;
							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* endDate;
							startDate = map->getProfessor(fourthLayer->getFirst())->getField(0);
							endDate = map->getProfessor(fourthLayer->getFirst())->getField(1);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* grant;
							grant = map->getProfessor(fourthLayer->getFirst())->getField(2);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* peer;
							peer = map->getProfessor(fourthLayer->getFirst())->getField(4);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* industry;
							industry = map->getProfessor(fourthLayer->getFirst())->getField(5);

							const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* funding;
							funding = map->getProfessor(fourthLayer->getFirst())->getField(10);

							//get date from gregorian date
							string startDateString;
							string endDateString;
							for (int i = 0; i < startDate->size(); i++){
								//check the type to see if it's the same
								if ((boost::get<string>(grant->at(i)).find(firstLayer->getFirst().substr(0, 5)) != string::npos)){
									//then check to see if peer or non-peer is the same
									bool check = boost::get<bool>(peer->at(i));
									if ((check && (secondLayer->getFirst().find("Peer") == 0)) || (!check && (secondLayer->getFirst().find("Peer") != 0))){
										//then check to see if industry or non-industry sponsored is the same
										check = boost::get<bool>(industry->at(i));
										if ((check && (thirdLayer->getFirst().find("Industry") == 0)) || (!check && (thirdLayer->getFirst().find("Industry") != 0))){
											startDateString = to_iso_string(boost::get<boost::gregorian::date>(startDate->at(i)));
											endDateString = to_iso_string(boost::get<boost::gregorian::date>(endDate->at(i)));
											if (((startDateString < low) || (startDateString > high)) && ((endDateString < low) || (endDateString > high))){
												//outside the filter

												for (auto &fifthLayer : *fourthLayer->getChildren()){
														fifthLayer->setVisible("date", true);
												}
												fourthLayer->setVisible("date", true);
												if (fourthLayer->getVisible() == true){
													//update hours
													fourthLayer->setFourth(fourthLayer->getFourth() + boost::get<float>(funding->at(i)));
													thirdLayer->setFourth(thirdLayer->getFourth() + boost::get<float>(funding->at(i)));
													secondLayer->setFourth(secondLayer->getFourth() + boost::get<float>(funding->at(i)));
													firstLayer->setFourth(firstLayer->getFourth() + boost::get<float>(funding->at(i)));
													root->setFourth(root->getFourth() + boost::get<float>(funding->at(i)));

													//update count numbers
													fourthLayer->setSecond(fourthLayer->getSecond() + 1);
													thirdLayer->setSecond(thirdLayer->getSecond() + 1);
													secondLayer->setSecond(secondLayer->getSecond() + 1);
													firstLayer->setSecond(firstLayer->getSecond() + 1);
													root->setSecond(root->getSecond() + 1);
												}
											}
										}
									}
								}
							}
						}
						thirdLayer->setVisible("date", true);
					}
					secondLayer->setVisible("date", true);
				}
				firstLayer->setVisible("date", true);
			}
			break;

		case professorMap::profType::Teaching:
			for (auto &firstLayer : *root->getChildren()){
				for (auto &secondLayer : *firstLayer->getChildren()){
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* startDate;
					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* endDate;
					startDate = map->getProfessor(secondLayer->getFirst())->getField(0);
					endDate = map->getProfessor(secondLayer->getFirst())->getField(1);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* program;
					program = map->getProfessor(secondLayer->getFirst())->getField(2);

					const vector<boost::variant<int, float, string, bool, boost::gregorian::date>>* profHours;
					profHours = map->getProfessor(secondLayer->getFirst())->getField(7);

					//get date from gregorian date
					string startDateString;
					string endDateString;
					for (int i = 0; i < startDate->size(); i++){
						//check the type to see if it's the same
						if (boost::get<string>(program->at(i)).compare(firstLayer->getFirst()) == 0){
							startDateString = to_iso_string(boost::get<boost::gregorian::date>(startDate->at(i)));
							endDateString = to_iso_string(boost::get<boost::gregorian::date>(endDate->at(i)));
							if (((startDateString < low) || (startDateString > high)) && ((endDateString < low) || (endDateString > high))){
								//outside the filter
								secondLayer->setVisible("date", true);
								if (secondLayer->getVisible() == true){
									//update hours
									secondLayer->setFourth(secondLayer->getFourth() + boost::get<float>(profHours->at(i)));
									firstLayer->setFourth(firstLayer->getFourth() + boost::get<float>(profHours->at(i)));
									root->setFourth(root->getFourth() + boost::get<float>(profHours->at(i)));
									//update count numbers
									secondLayer->setSecond(secondLayer->getSecond() + 1);
									firstLayer->setSecond(firstLayer->getSecond() + 1);
									root->setSecond(root->getSecond() + 1);
								}
							}
						}
					}
				}
				firstLayer->setVisible("date", true);
			}
			break;
		}
	}
};