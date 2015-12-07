#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabBar>
#include <QToolButton>
#include <QAbstractButton>
#include <QTabWidget>
#include <QLabel>
#include <QString>
#include <stdlib.h>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QShortcut>
#include "professorMap.h"
#include "node.h"
#include "statisticsTree.h"
#include "listview.h"
#include "legendwidget.h"
#include "piechartwidget.h"
#include "barplot.h"
#include "helpdialog.h"

class QMdiArea;
class QMdiSubWindow;
class QPrinter;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void addModel(professorMap* data){ this->data = data; }
private slots:

    void on_actionImport_CSV_triggered();

    void on_actionGenerate_Pie_Chart_triggered();

    void on_actionGenerate_Bar_Graph_triggered();

    void on_actionSave_Graph_triggered();

	void generateList(node*);

	void refreshSubWindows();

	void on_actionData_Filter_Options_triggered();

	void on_actionOpen_Help_triggered();

	void on_actionPrint_Graph_triggered();

	void on_actionPrint_Graph_Preview_triggered();

	void print(QPrinter*);

	void on_actionPrint_List_triggered();

	void on_actionPrint_List_Preview_triggered();

	void printList(QPrinter*);

	void on_addFilter_clicked();

	void on_updateGraph_clicked();

	void findPosition(QTreeWidgetItem*, vector<int>*);

private:
    Ui::MainWindow *ui;
    std::string file_name;
	professorMap* data;
	node* rootNode;
	QMdiArea *m_area;
	QMdiSubWindow *bar;
	QMdiSubWindow *pie;
	QMdiSubWindow *tree;
	bool csv = false;
	QRect rec;
	ListView* list;
	PieChartWidget* pieChart;
	LegendWidget* legend;
	BarPlot* barPlot;
};

#endif // MAINWINDOW_H
