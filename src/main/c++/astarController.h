#pragma once
#include "csvHolder.h"
#include "professor.h"

class astarController {
private:
	csvHolder* Model;
	//view*	    View;
public:
	astarController();
	astarController(csvHolder* model);
};