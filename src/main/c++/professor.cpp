#include "stdafx.h"
#include <string>
#include "professor.h"

using namespace std;
professor::professor() { this->name = ""; }
professor::professor(string name) { this->name = name; }
professor::professor(professor& orig) { this->name = orig.name; }
professor::~professor() {}

string professor::getName() { return this->name; }
string professor::setName(string name) { return this->name = name; };