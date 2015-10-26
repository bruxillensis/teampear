#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <string.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > >);
    ~MainWindow();
    string getFileName();
    void setVector(std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > >);


private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_actionPie_Chart_triggered();

    void on_actionImport_CSV_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > vector;
    string file_name;
};

#endif // MAINWINDOW_H
