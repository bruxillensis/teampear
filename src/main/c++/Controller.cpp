#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>
#include "controller.h"
#include <string.h>
#include "mainwindow.h"
#include "pubProfessor.h"
#include "professorMap.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>

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
    newPair = data->callMe(0,2015);// temp hardcode date (Henry)
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

string Controller::getFileName(){
    QString filename = QFileDialog::getOpenFileName(
                0,
                "Select a CSV file",
                QDir::homePath(),
                "CSV files (*.csv)"
                );
    return filename.toStdString();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller *newController;
    string filename = newController->getFileName();
    professorMap<pubProfessor>* newData = new professorMap<pubProfessor>();
    newData->importCSV(filename);
    MainWindow *newWindow = new MainWindow(0, newData->callMe(0,2015)); // temp hard code date (Henry)
   newController = new Controller(newWindow, newData);
    newWindow = newController->draw();

    newWindow->show();
    a.exec();

    return 0;
}
