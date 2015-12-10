#pragma once
#include "node.h"

using namespace std;

class filter {
private:
	
public:
	void applyFilter(node* root);
	virtual void removeFilter(){}
};