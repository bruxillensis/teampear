#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>
#include <Controller.h>
#include <vector>
#include <string.h>
using namespace std;

Controller::Controller(MainWindow view, professorMap data)
{
    this->view = view;
    this->data = data.callMe();
}

void Controller::dataFilter(string d1, string d2)
{

}

MainWindow Controller::draw()
{
    vector<pair<string,vector<pair<string,string>>>> newPair;
    newPair = pair;
    return MainWindow(0,newPair);
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
    MainWindow *newWindow;
    professorMap newData;
    string filename = newWindow->getFileName();
    newData.importCSV(filename);
    Controller newController = new Controller(newData,newWindow);
    newWindow = newController.draw();

    newWindow->show();
    a.exec();

    return 0;
}
