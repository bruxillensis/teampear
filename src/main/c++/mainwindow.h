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
#include "professorMap.h"
#include "node.h"
#include "statisticsTree.h"

class QMdiArea;
class QMdiSubWindow;

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

    void on_actionPrint_Graph_triggered();

	void generateList(node*);

	void refreshSubWindows();


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
};

#endif // MAINWINDOW_H
