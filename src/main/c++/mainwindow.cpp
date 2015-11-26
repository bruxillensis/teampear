#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pubTree.h"
#include "granTree.h"
#include "teacTree.h"
#include "presTree.h"
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
#include "listview.h"
#include "piechartwidget.h"
#include "legendwidget.h"
#include "barplot.h"
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->showMaximized();
	rec = QApplication::desktop()->screenGeometry();
	this->setFixedSize(rec.size());
	this->m_area = new QMdiArea;
	this->setCentralWidget(m_area);
}



MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionImport_CSV_triggered()
{
	// Refresh the subWindows each time a new CSV is imported
	refreshSubWindows();

	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"C://",
		"CSV files (*.csv)"
		);

	QMessageBox::information(this, tr("File Name"), filename);
	file_name = filename.toStdString();

	if (!(file_name.empty())){
		//import the csv file and get the professor type
		professorMap::profType type = this->data->importCSV(file_name);


		csv = true;
		statisticsTree* tree;

		switch (type){
		case professorMap::profType::Publication:
			tree = new pubTree(this->data);
			break;
		case professorMap::profType::Presentation:
			tree = new presTree(this->data);
			break;
		case professorMap::profType::GrantClinical:
			tree = new granTree(this->data);
			break;
		case professorMap::profType::Teaching:
			tree = new teacTree(this->data);
			break;
		default:
			//didn't find the type of professor
			break;
		}
		this->rootNode = tree->getStatistics();
		generateList(this->rootNode); // generate tree with the data
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
	if (csv){
		BarPlot *barPlot = new BarPlot(this);
		//display the right subwindow
		this->pie->hide();
		this->bar->setVisible(true);
		this->bar->setGeometry(rec.width() / 2, 0, rec.width() / 2, rec.height() - 120);
		barPlot->plotBar(this->rootNode);
		this->bar->setWidget(barPlot);
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
	if (csv){
		PieChartWidget *piechart = new PieChartWidget;
		LegendWidget *legend = new LegendWidget;
		QSplitter *splitter = new QSplitter;

		// display the right subwindow
		this->bar->hide();
		this->pie->setVisible(true);
		this->pie->setGeometry(rec.width() / 2, 0, rec.width() / 2, rec.height() - 120);
		//draw piechart and legend
		piechart->setData(this->rootNode);
		legend->drawLegend(this->rootNode);

		// add a plottable area and legend
		splitter->addWidget(piechart);
		splitter->addWidget(legend);
		splitter->setStretchFactor(0, 0);
		splitter->setStretchFactor(1, 2);
		this->pie->setWidget(splitter);
	}
	else
	{
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: Cannot generate pie chart. No data has been loaded."));
	}
}

void MainWindow::generateList(node* root)
{
	//create a new list view
	ListView *view = new ListView(this);
	view->makeList(root);
	// call the thing that populates it
	int i;
	for (i = 0; i < view->columnCount(); i++)
	{
		view->resizeColumnToContents(i);
	}
	this->tree->setVisible(true);
	this->tree->setWidget(view);
	this->tree->setGeometry(0, 0, rec.width() / 2, rec.height() - 120);
}

void MainWindow::on_actionSave_Graph_triggered()
{
	QPixmap originalPixmap;

	if (this->bar->isVisible()){
		this->bar->setGeometry(rec.width(), 0, rec.width(), rec.height()); //fullscreen
		QPixmap originalPixmap = QPixmap::grabWidget(this->bar);
		this->bar->setGeometry(rec.width() / 2, 0, rec.width() / 2, rec.height() - 120); //resize back to original
	}
	if (this->pie->isVisible()){
		QPixmap originalPixmap = QPixmap::grabWidget(this->pie);
	}

	QString fileName = QFileDialog::getSaveFileName(
		this,
		tr("Save File"),
		"C://",
		"PNG files (*.png)"
		);
	originalPixmap.save(fileName);
	
}

void MainWindow::on_actionPrint_Graph_triggered()
{

}

void MainWindow::refreshSubWindows()
{
	if (this->m_area->subWindowList().size() > 0){
		this->m_area->closeAllSubWindows();
	}

	this->m_area->setTabsMovable(false);
	// create three subwindows for (bar graph, pie chart, tree widget)
	// remove their window flags, set fixed dimensions
	this->tree = new QMdiSubWindow(m_area);
	this->tree->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	this->bar = new QMdiSubWindow(m_area);
	this->bar->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	this->pie = new QMdiSubWindow(m_area);
	this->pie->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	//hide subwindows until called on plot
	this->tree->hide();
	this->bar->hide();
	this->pie->hide();

	// prevent user from moving the windows
	//this->tree->setDisabled(true);
	//this->bar->setDisabled(true);
	//this->pie->setDisabled(true);
}