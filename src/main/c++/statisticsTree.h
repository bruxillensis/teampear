#pragma once
#include <string>
#include <vector>
#include "node.h"

using namespace std;

template <class T>
class statisticsTree {
private:
	node* root;

	void createPubStatistics(professorMap<T>* profMap){}
	void createTeacStatistics(professorMap<T>* profMap){}
	void createGranStatistics(professorMap<T>* profMap){}
	void createPresStatistics(professorMap<T>* profMap){}

public:
	statisticsTree(){
		root = NULL;
	}
	statisticsTree(professorMap<T>* profMap){
		statisticsTree();
		createStatistics(profMap);
	}
	node* getStatistics(){ return root; }
	void createStatistics(professorMap<T>* profMap) {
		//Requires C++11 to use is_same
		//If type is of pubProfessor do
		if (std::is_same<T, pubProfessor>::value) {
			createPubStatistics(profMap);
		}
		//If type is of teachProfessor do
		if (std::is_same<T, teacProfessor>::value) {
			createTeacStatistics(profMap);
		}
		//If type is of granProfessor do
		if (std::is_same<T, granProfessor>::value) {
			createGranStatistics(profMap);
		}
		//If type is of presProfessor do
		if (std::is_same<T, presProfessor>::value) {
			createPresStatistics(profMap);
		}
	}
};