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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newTabButton_clicked()
{
    ui->tabWidget->insertTab(ui->tabWidget->count(), new tabLayoutWidget(), QIcon(QString("")), "New Tab");
	ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::on_deleteTabButton_clicked()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
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
		pubTree* test = new pubTree(this->data);
}

//make widget that appears in mdiarea of the tab
void MainWindow::on_actionGenerate_Pie_Chart_triggered()
{
	return;
}

//make widget that appears in mdiarea of the tab
void MainWindow::on_actionGenerate_Bar_Graph_triggered()
{
	return;
}

void MainWindow::on_actionSave_Graph_triggered()
{
	return;
}

void MainWindow::on_actionPrint_Graph_triggered()
{
	return;
}
