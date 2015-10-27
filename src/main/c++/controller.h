#pragma once
#include "professorMap.h"
#include "mainwindow.h"
#include "pubprofessor.h"
#include <string.h>

using namespace std;

class Controller
{
    private:
        professorMap<pubProfessor>* data;//the model class
        MainWindow* view;//view class
        //implement Datacheck class
    public:
        //Controller();
        Controller(MainWindow*, professorMap<pubProfessor>*);//constructor
        void dataFilter(string, string); //check whether the two dates are correct
        MainWindow* draw();
};
