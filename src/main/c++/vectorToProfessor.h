#pragma once
#include <string>
#include "csvHolder.h"
#include "professor.h"
#include "pubProfessor.h"

using namespace std;

class vectorToProfessor {
public:
	//Create professor object, filling in all information and pass reference back
	pubProfessor* createProfessor(string professorName, csvHolder& modelArray);
};