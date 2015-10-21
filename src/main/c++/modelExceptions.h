#pragma once
#include <exception>

using namespace std;

class indexOutOfBoundsException : public exception{
	virtual const char* what() const throw(){return "Index is out of bounds of vector entries";}
};

class professorNotFoundException : public exception {
	virtual const char* what() const throw() { return "Professor was not found"; }
};

//CAN ADD ALL EXCEPTION CLASSES HERE