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

class invalidDateException : public exception {
public:
	virtual const char* what() const throw() { return "Date is not valid"; }
};

class failedTypeChangeException : public exception {
public:
	virtual const char* what() const throw() { return "Type could not be converted from string"; }
};
//CAN ADD ALL EXCEPTION CLASSES HERE