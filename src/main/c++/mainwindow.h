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


private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_clicked();

    void on_actionPie_Chart_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
