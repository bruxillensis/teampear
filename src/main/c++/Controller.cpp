#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>
#include <Controller.h>
#include <string.h>
#include "mainwindow.h"
#include "pubProfessor.h"
#include "professorMap.h"

using namespace std;

Controller::Controller(MainWindow* view, professorMap<pubProfessor>* data)
{
    this->view = view;
    this->data = data;
}


void Controller::dataFilter(std::string d1, std::string d2)
{

}

MainWindow* Controller::draw()
{
    vector<pair<std::string,vector<pair<std::string,int>>>> newPair;
    newPair = data->callMe();
    return new MainWindow(0,newPair);
    //fullData
//    std::pair<std::string,std::vector<std::pair<std::string,std::string> > > p;
//    //
//    std::pair<std::string,std::string> s;

//    s.first = std::string("dfas the idiot");
//    s.second = std::string("12");

//    std::vector<std::pair<std::string,std::string> > p2;

//    p2.push_back(s);
//    p2.push_back(s);
//    p2.push_back(s);
//    p.first = std::string("Multimedia");
//    p.second = p2;

//    q.push_back(p);
//    q.push_back(p);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    professorMap<pubProfessor>* newData = new professorMap<pubProfessor>();
    newData->importCSV("C:/Users/Owner/Desktop/TeamPearUI2/TeamPearUI/Publications_sample.csv");
    MainWindow *newWindow = new MainWindow(0, newData->callMe());
    Controller *newController = new Controller(newWindow, newData);
    newWindow = newController->draw();

    newWindow->show();
    a.exec();

    return 0;
}
