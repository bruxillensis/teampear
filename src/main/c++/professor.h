#pragma once
#include <string>

using namespace std;

class professor {
private:
	string name;

public:
	professor();
	professor(string name);
	virtual ~professor();

	string getName();
	string setName();
};