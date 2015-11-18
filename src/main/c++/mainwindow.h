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
#include "tablayoutwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newTabButton_clicked();

    void on_deleteTabButton_clicked();

    void on_actionImport_CSV_triggered();

    void on_actionGenerate_Pie_Chart_triggered();

    void on_actionGenerate_Bar_Graph_triggered();

    void on_actionSave_Graph_triggered();

    void on_actionPrint_Graph_triggered();

private:
    Ui::MainWindow *ui;
    std::string file_name;


};

#endif // MAINWINDOW_H
