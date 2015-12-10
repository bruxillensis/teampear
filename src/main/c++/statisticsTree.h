#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "professorMap.h"
#include "professor.h"
using namespace std;

/*
Returns organized statistics of a professor type.

ex.
returns for Publications a tree organized like so
	Publications (root)
		Book Chapters
			Prof A, Number of pubs of type Book Chapters
			Prof B, Number of pubs of type Book Chapters
		Books
			Prof A, Number of pubs of type Book
etc.
*/

class statisticsTree {
protected:
	node* root;
public:
	statisticsTree(){
		root = NULL;
	}
	statisticsTree(professorMap* professors){
		statisticsTree();
		createStatistics(professors);
	}
	~statisticsTree(){ delete root; }
	node* getStatistics(){ return root; }
	virtual void createStatistics(professorMap* professors){}
	virtual void addFilter(){}
	virtual void removeFilter(){}
	void getTotals(){
		recursiveSecondTotalling(this->root);
		recursiveFourthTotalling(this->root);
	}
	int recursiveSecondTotalling(node* n){
		if (n->getChildren()->size() == 0)
			return n->getSecond();
		else{
			int c = 0;
			for (auto i : *(n->getChildren()))
				c += recursiveSecondTotalling(i);
			n->setSecond(c);
			return c;
		}
	}
	float recursiveFourthTotalling(node* n){
		if (n->getChildren()->size() == 0)
			return n->getFourth();
		float c = 0;
		for (auto i : *(n->getChildren()))
			c += recursiveFourthTotalling(i);
		n->setFourth(c);
		return c;
	}
};