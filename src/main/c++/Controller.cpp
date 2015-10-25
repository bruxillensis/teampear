#pragma once
#include <string>
#include <vector>
#include "professorMap.h"
#include "errorHandling.h"
#include "mainwindow.h"
#include "QTlibrary"//whatever QT is here
#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <utility>
#include <QPair>


using namespace std;

class Controller {

	private:
		professorMap professor; //create a professor model
		mainwindow view; //QT object


	public: //replace the events with QT syntax
 		Controller(QTView, createProfessor); //create a constructor that takes in a view and createProfessor object
		void dateFilter(string, string);//passes the date range from view to model
		void inputData(string, vector<vector<string>>);//passes model information to view
		//the second paramter is a 2d vector
		void errorCheck(string, string);//checks the error in date range entered
        void passData();

		void mouseClicked(MouseEvent); //if mouse is clicked, you would expand	 
		void graphChange(ListSelectionEvent); //if a different graph is selected
		void filter();
};

//implementation

Controller::Controller(mainwindow view, professorMap professor, errorHandling checkError)
{
	view = new mainwindow();
	professor = new professorMap();
}

void passData()
{
    std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > >  data;
    data = professor.getInfo();
    view.setVector(data);
    view.exec();
}

void Controller::dateFilter()
{//takes the date range from view 
	//call errorHandling class to check it
	string fDate, sDate;
	fDate = view.getFirstDate();
	sDate = view.getSecondDate();
	bool isValid = checkError.checkYearRange(fDate, sDate);

}

void Controller::mouseClicked(MouseEvent event){
//when mouse have been clicked
//get the location of the point
//store the point or use the point
//repaint
}

void Controller::graphChange(ListSelectionEvent event){
//get the new graph type
//set the new graph
//repaint
}

void Controller::filter()
{
	
}

int main()
{
    string filename = "public.csv";
    QApplication a(argc, argv);
    MainWindow w;//create the MainWindow, view
    professorMap data = new professorMap(filename);//create the model
    Controller newController = new Controller(w, data);//pass in the model and the view
    newController.passData();//run the program

    return 0;
}



