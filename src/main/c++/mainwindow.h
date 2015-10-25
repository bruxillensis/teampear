#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setVector(std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > >);
    std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > getVector();

private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_actionPie_Chart_triggered();

    void on_actionAdd_CSV_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
