#pragma once
#include <exception>

using namespace std;

class indexOutOfBoundsException : public exception{
public:
	virtual const char* what() const throw(){return "Index is out of bounds of vector entries";}
};

class professorNotFoundException : public exception {
public:
	virtual const char* what() const throw() { return "Professor was not found"; }
};

class manditoryHeaderNotFoundException : public exception {
public:
	virtual const char* what() const throw() { return "Manditory header was not found"; }
};

class emptyManditoryCellException : public exception {
public:
	virtual const char* what() const throw() { return "Manditory cell is empty"; }
};

class yearNotSpecifiedException : public exception {
public:
	virtual const char* what() const throw() { return "Year was not specified"; }
};
//CAN ADD ALL EXCEPTION CLASSES HERE