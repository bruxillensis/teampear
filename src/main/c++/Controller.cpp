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
    //vector<pair<std::string,vector<pair<std::string,int>>>> newPair;
    //newPair = data->callMe(0,2015);// temp hardcode date (Henry)
    return new MainWindow();
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
    MainWindow *newWindow = new MainWindow(); // temp hard code date (Henry)
	newController = new Controller(newWindow, newData);
    newWindow = newController->draw();

    newWindow->show();
    a.exec();

    return 0;
}
