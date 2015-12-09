#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pubTree.h"
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
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPrintDialog>

#include "granTree.h"
#include "teacTree.h"
#include "presTree.h"
#include "listview.h"
#include "piechartwidget.h"
#include "legendwidget.h"
#include "barplot.h"
#include "filterdialog.h"
#include "node.h"
#include "helpdialog.h"
#include "countFilter.h"
#include "hourFilter.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->showMaximized();
	rec = QApplication::desktop()->screenGeometry();
	this->setFixedSize(rec.size());
	this->m_area = new QMdiArea;
	//this->setCentralWidget(m_area);
	this->rootNode = NULL;
	this->bar = NULL;
	this->pie = NULL;
	this->barPlot = NULL;
	this->pieChart = NULL;
	this->legend = NULL;
	this->list = NULL;
	this->ui->verticalLayout_2->addWidget(this->m_area);
    //set up hotkeys
    new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_I), this, SLOT(on_actionImport_CSV_triggered()));
	new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_C), this, SLOT(on_actionGenerate_Pie_Chart_triggered()));
	new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_B), this, SLOT(on_actionGenerate_Bar_Graph_triggered()));
	new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_S), this, SLOT(on_actionSave_Graph_triggered()));
	new QShortcut(QKeySequence(Qt::Key_Control + Qt::Key_H), this, SLOT(on_actionOpen_Help()));
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
	file_name = filename.toStdString();

	if (!(file_name.empty())){
		//import the csv file and get the professor type
		statisticsTree* tree;
		if (this->rootNode != NULL){
			delete this->rootNode;
			delete this->data;
			this->addModel(new professorMap());
		}
		
		try{
			csv = true;
			this->type = this->data->importCSV(file_name);

			switch (this->type){
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
		catch (manditoryHeaderNotFoundException& e){
			QErrorMessage msg;
			msg.showMessage(QString("Mandatory headers not found. There are spelling errors in the column names."));
			msg.exec();
			cerr << e.what();
			this->rootNode=NULL;
		}
		catch (typeNotRecognizedException& e){
			QErrorMessage msg;
			msg.showMessage(QString(e.what()));
			msg.exec();
			cerr << e.what();
			this->rootNode = NULL;
		}
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
		this->barPlot = new BarPlot(this);
		//display the right subwindow
		this->pie->hide();
		this->bar->setVisible(true);
		this->bar->setGeometry(rec.width() / 2 - 11, 0, rec.width() / 2 - 11, rec.height() - 165);
		int extra = this->barPlot->plotBar(this->rootNode);
		this->bar->setWidget(this->barPlot);

		if (extra == 1){
			QErrorMessage* noCSV = new QErrorMessage();;
			noCSV->showMessage(QString("Due to the large number of different types, only the 20 greatest ones are shown.\
									   The rest have been compiled into 'Others'."));
		}
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
		this->pieChart = new PieChartWidget;
		this->legend = new LegendWidget;
		QSplitter *splitter = new QSplitter;

		// display the right subwindow
		this->bar->hide();
		this->pie->setVisible(true);
		this->pie->setGeometry(rec.width() / 2 - 11, 0, rec.width() / 2 - 11, rec.height() - 165);
		//draw piechart and legend
		this->pieChart->setData(this->rootNode);
		this->legend->drawLegend(this->rootNode);

		// add a plottable area and legend
		splitter->addWidget(this->pieChart);
		splitter->addWidget(this->legend);
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
	this->list = new ListView(this);
	this->list->makeList(root);
	// call the thing that populates it
	int i;
	for (i = 0; i < this->list->columnCount(); i++)
	{
		this->list->resizeColumnToContents(i);
	}
	this->tree->setVisible(true);
	this->tree->setWidget(this->list);
	this->tree->setGeometry(0, 0, rec.width() / 2 - 11, rec.height() - 165);

}

void MainWindow::on_actionSave_Graph_triggered()
{
	QPixmap originalPixmap;
	if (this->bar == NULL && this->pie==NULL){
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: No graph to save."));
		noCSV->exec();
		return;
	}
	if (this->bar->isVisible()){
		this->bar->setGeometry(rec.width(), 0, rec.width(), rec.height()); //fullscreen
		originalPixmap = QPixmap::grabWidget(this->bar);
		this->bar->setGeometry(rec.width() / 2 - 11, 0, rec.width() / 2 - 11, rec.height() - 165); //resize back to original
	}
	if (this->pie->isVisible()){
		originalPixmap = QPixmap::grabWidget(this->pie);
	}

	QString fileName = QFileDialog::getSaveFileName(
		this,
		tr("Save File"),
		"C://",
		tr("Image Files(*.png *.jpg *.bmp)")
		);
	originalPixmap.save(fileName);
	
}

void MainWindow::refreshSubWindows()
{
	if (this->m_area->subWindowList().size() > 0){
		this->m_area->closeAllSubWindows();
		if (this->list != NULL){
			delete this->list;
			this->list = NULL;
		}
		if (this->barPlot != NULL){
			delete this->barPlot;
			this->barPlot = NULL;
		}
		if (this->pieChart != NULL){
			delete this->pieChart;
			delete this->legend;
			this->pieChart = NULL;
			this->legend = NULL;
		}
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

void MainWindow::on_actionData_Filter_Options_triggered()
{
	filterDialog d;
	d.setModal(true);
	d.exec();
}

void MainWindow::on_actionOpen_Help_triggered(){
	helpDialog d;
	d.setModal(true);
	d.exec();
}

void MainWindow::on_actionPrint_Graph_triggered()
{
	if (this->bar == NULL && this->pie == NULL){
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: No graph to print."));
		noCSV->exec();
		return;
	}
	// display print dialog and if accepted print
	QPrinter       printer(QPrinter::HighResolution);
	QPrintDialog   dialog(&printer, this);
	if (dialog.exec() == QDialog::Accepted) print(&printer);
}

void MainWindow::on_actionPrint_Graph_Preview_triggered()
{
	if (this->bar == NULL && this->pie == NULL){
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: No graph to print."));
		noCSV->exec();
		return;
	}
	// display print preview dialog
	QPrinter             printer(QPrinter::HighResolution);
	QPrintPreviewDialog  preview(&printer, this);
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)));
	preview.exec();
}

void MainWindow::print(QPrinter* printer)
{
	// create painter for drawing print page
	QPainter painter;
	int      w = printer->pageRect().width();
	int      h = printer->pageRect().height();
	QRect    page(0, 0, w, h);

	// create a font appropriate to page size
	QFont    font = painter.font();
	font.setPixelSize((w + h) / 100);
	painter.setFont(font);
	painter.begin(printer);

	// draw labels in corners of page
	painter.drawText(page, Qt::AlignTop | Qt::AlignLeft, QString::fromStdString(rootNode->getFirst()));
	painter.drawText(page, Qt::AlignBottom | Qt::AlignLeft, QString(getenv("USER")));
	painter.drawText(page, Qt::AlignBottom | Qt::AlignRight,
		QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate));

	// draw simulated landscape
	page.adjust(w / 20, h / 20, -w / 20, -h / 20);
	QPixmap printPixmap;
	if (this->bar->isVisible()){
		this->bar->setGeometry(rec.width(), 0, rec.width(), rec.height()); //fullscreen
		printPixmap = QPixmap::grabWidget(this->bar);
		this->bar->setGeometry(rec.width() / 2 - 11, 0, rec.width() / 2 - 11, rec.height() - 165); //resize back to original
	}

	if (this->pie->isVisible()){
		printPixmap = QPixmap::grabWidget(this->pie);
	}
	printPixmap = printPixmap.scaled(w, h, Qt::KeepAspectRatio);
	painter.drawPixmap(0, 100, printPixmap);
	painter.end();
	
}

void MainWindow::on_actionPrint_List_triggered()
{
	if (this->list == NULL){
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: No list to print."));
		noCSV->exec();
		return;
	}
	// display print dialog and if accepted print
	QPrinter       printer(QPrinter::ScreenResolution);
	QPrintDialog   dialog(&printer, this);
	if (dialog.exec() == QDialog::Accepted) printList(&printer);
}

void MainWindow::on_actionPrint_List_Preview_triggered()
{
	if (this->list == NULL){
		QErrorMessage* noCSV = new QErrorMessage();;
		noCSV->showMessage(QString("ERROR: No list to print."));
		noCSV->exec();
		return;
	}
	// display print preview dialog
	QPrinter             printer(QPrinter::ScreenResolution);
	QPrintPreviewDialog  preview(&printer, this);
	connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printList(QPrinter*)));
	preview.exec();
}

void MainWindow::printList(QPrinter* printer)
{
	// create painter for drawing print page
	QPainter painter;
	int      w = printer->pageRect().width();
	int      h = printer->pageRect().height();
	QRect    page(0, 0, w, h);

	// create a font appropriate to page size
	QFont    font = painter.font();
	font.setPixelSize((w + h) / 100);
	painter.setFont(font);
	painter.begin(printer);

	// draw labels in corners of page
	painter.drawText(page, Qt::AlignTop | Qt::AlignLeft, QString::fromStdString(rootNode->getFirst()));
	painter.drawText(page, Qt::AlignBottom | Qt::AlignLeft, QString(getenv("USER")));
	painter.drawText(page, Qt::AlignBottom | Qt::AlignRight,
		QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate));

	// draw simulated landscape
	page.adjust(w / 20, h / 20, -w / 20, -h / 20);
	QPixmap printPixmap;
	printPixmap = QPixmap::grabWidget(this->tree);

	printPixmap = printPixmap.scaled(w, h, Qt::KeepAspectRatio);
	painter.drawPixmap(0, 100, printPixmap);
	painter.end();
}

void MainWindow::on_addFilter_clicked()
{
	filterDialog* d = new filterDialog();
	d->setModal(true);
	d->exec();
	//d.findChild<QCheckBox*>("dateCheckBox")->isChecked();
	//d.findChild<QCheckBox*>("domainCheckBox")->isChecked();
	//d.findChild<QCheckBox*>("fundingCheckBox")->isChecked();
	//d.findChild<QCheckBox*>("hourCheckBox")->isChecked();
	if (d->isCountChecked()){
		countFilter* filter = new countFilter(d);
		filter->applyFilter(this->rootNode, this->type);
	}
	if (d->isHoursChecked()){
		hourFilter* filter = new hourFilter(d);
		filter->applyFilter(this->rootNode, this->data);
	}
	if (this->list != NULL){
		delete this->list;
		this->generateList(this->rootNode);
	}
	delete d;
}

void MainWindow::on_updateGraph_clicked()
{
	QTreeWidgetItem* n = this->list->currentItem();
	if (n->parent() == NULL || n->childCount() == 0)
		return;
	vector<int>* position = new vector<int>();

	if (n->parent() != NULL){
		position->push_back(n->parent()->indexOfChild(n));
		findPosition(n->parent(), position);
	}
	node* val = this->rootNode;
	position->pop_back();
	for (vector<int>::reverse_iterator it = position->rbegin(); it != position->rend(); ++it)
		val = val->getChildren()->at(*it);
	if (this->barPlot != NULL){
		delete this->barPlot;
		this->barPlot = new BarPlot(this);
		this->barPlot->plotBar(val);
		this->bar->setWidget(this->barPlot);
	}
	if (this->pieChart != NULL){
		this->pieChart->setData(val);
		this->legend->drawLegend(val);
	}
}

void MainWindow::findPosition(QTreeWidgetItem* n, vector<int>* position){
	if (n->parent() != NULL){
		position->push_back(n->parent()->indexOfChild(n));
		findPosition(n->parent(), position);
	}
}
