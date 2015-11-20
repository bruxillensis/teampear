#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>
#include "controller.h"
#include <string.h>
#include "mainwindow.h"
#include "professorMap.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMainWindow>
#include "pubTree.h"
#include "presTree.h"
#include "granTree.h"
#include "teacTree.h"

using namespace std;

Controller::Controller(MainWindow* view, professorMap* data)
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
    Controller *controller;
	controller = new Controller(new MainWindow(), new professorMap());
	controller->getWindow()->addModel(controller->getModel());
    controller->getWindow()->show();
    a.exec();

    return 0;
}