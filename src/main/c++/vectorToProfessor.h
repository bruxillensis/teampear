#pragma once
#include <string>
#include "csvHolder.h"
#include "professor.h"
using namespace std;

class vectorToProfessor{
private:
	csvHolder* Array;
	professor* Professor;
public:

	vectorToProfessor();
	vectorToProfessor(csvHolder* array);

	//Create professor object, filling in all information and pass reference back
	professor* createProfessor(string professorName);
};