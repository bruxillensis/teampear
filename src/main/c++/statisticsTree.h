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
};
