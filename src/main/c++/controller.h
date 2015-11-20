#pragma once
#include "professorMap.h"
#include "mainwindow.h"
#include <string>

using namespace std;

class Controller
{
    private:
        professorMap* data;//the model class
        MainWindow* view;//view class
        //implement Datacheck class
    public:
        //Controller();
        Controller(MainWindow*, professorMap*);//constructor
        void dataFilter(string, string); //check whether the two dates are correct
        string getFileName();
        MainWindow* draw();
		MainWindow* getWindow(){ return this->view; }
		professorMap* getModel(){ return this->data; }
};
