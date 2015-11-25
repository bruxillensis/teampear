#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pubTree.h"
#include "bardialog.h"

#include <utility>
#include <string>
#include <vector>
#include <QTCore>
#include <QtGui>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QRect>
#include <QObject>
#include <QErrorMessage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->showMaximized();

	// get the size of the desktop screen
	QRect rec = QApplication::desktop()->screenGeometry();
	int h = rec.height();
	int w = rec.width();

	// Create a new MDI area
	this->m_area = new QMdiArea;
	
	// create three subwindows for (bar graph, pie chart, tree widget)
	// remove their window flags, set fixed dimensions
	this->tree = new QMdiSubWindow(m_area);
	this->tree->setWindowFlags(Qt::CustomizeWindowHint);
	this->tree->setFixedWidth(w / 2);
	this->tree->setFixedHeight(h - 120);

	this->bar = new QMdiSubWindow(m_area);
	this->bar->setWindowFlags(Qt::CustomizeWindowHint);
	this->bar->setFixedWidth(w / 2);
	this->bar->setFixedHeight(h - 120);

	this->pie = new QMdiSubWindow(m_area);
	this->pie->setWindowFlags(Qt::CustomizeWindowHint);
	this->pie->setFixedWidth(w / 2);
	this->pie->setFixedHeight(h - 120);

	//hide subwindows until called on plot
	this->tree->hide();
	this->bar->hide();
	this->pie->hide();

	// set the location and size of the plot subwindows
	this->pie->setGeometry(w / 2, 0, w / 2, h - 120);
	this->bar->setGeometry(w/2, 0, w / 2, h - 120);

	// prevent user from moving the windows
	this->tree->setDisabled(true);
	this->bar->setDisabled(true);
	this->pie->setDisabled(true);

	this->setCentralWidget(m_area);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImport_CSV_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                    "CSV files (*.csv)"
                    );

        QMessageBox::information(this, tr("File Name"), filename);
        file_name = filename.toStdString();
		//Hardcode
		this->data->importCSV(file_name, professorMap::profType::Publication);
		if (data->getProfessorCount() > 0){
			csv = true;
			pubTree* test = new pubTree(this->data); // hardcoded type of csv (temp)
			this->rootNode = test->getStatistics();
			populateTree();
		}
		else
		{
			QErrorMessage* noCSV = new QErrorMessage();;
			noCSV->showMessage(QString("ERROR: No CSV was chosen."));
		}
}

//make widget that appears in mdiarea of the tab
void MainWindow::on_actionGenerate_Bar_Graph_triggered()
{
	QCustomPlot *customPlot = new QCustomPlot;
	if (csv){
		this->pie->hide();
		this->bar->setVisible(true);
		this->bar->setWidget(customPlot);
		//BarDialog barPlot(
	}
	else
	{
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: Cannot generate bar graph. No data has been loaded."));
	}
}

//make widget that appears in mdiarea of the tab
void MainWindow::on_actionGenerate_Pie_Chart_triggered()
{
	QWidget *piePlot = new QWidget;
	if (csv){
		this->bar->hide();
		this->pie->setVisible(true);
		this->pie->setWidget(piePlot);
	}
	else
	{
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: Cannot generate pie chart. No data has been loaded."));
	}
}

void MainWindow::populateTree()
{
	// Andy and Max should fill this out
	this->tree->setVisible(true);
}

void MainWindow::on_actionSave_Graph_triggered()
{

}

void MainWindow::on_actionPrint_Graph_triggered()
{

}

