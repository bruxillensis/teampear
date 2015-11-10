#include "piedialog.h"
#include "ui_piedialog.h"
#include "piechartwidget.h"
#include <QGridLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QSplitter>
#include <iostream>

using namespace std;

PieDialog::PieDialog(QWidget *parent, std::vector<std::pair<std::string,std::vector<std::pair<std::string,int> > > > vector) :
    QDialog(parent),
    ui(new Ui::PieDialog)
{
    ui->setupUi(this);
    PieChartWidget *widget = new PieChartWidget();
    widget->setData(vector);
    setWindowTitle(tr("Total Publication Types"));
    QGridLayout *layout = new QGridLayout;

    QTableView *legend = new QTableView();
    legend->setMinimumWidth(175);
    QStandardItemModel *model = new QStandardItemModel(21, 2, this);
    model->setHeaderData(1, Qt::Horizontal, tr("Publication Type"));
    model->setHeaderData(0, Qt::Horizontal, tr(" "));

    int i, currentHue= 0,j, rows = 0, current;
    for(i=0; i < vector.size(); i++){
        current = 0;
        for(j = 0 ; j < vector.at(i).second.size(); j++){
            current += vector.at(i).second.at(j).second;
        }
        if(current > 0){
            QColor current_color;
            current_color.setHsv(currentHue,210,255);
            model->setItem(rows,1, new QStandardItem(QString::fromStdString(vector.at(i).first)));
            model->setItem(rows, 0, new QStandardItem(QString::fromStdString("")));
            model->item(rows, 0)->setData(QBrush(current_color),Qt::BackgroundRole);
            cout << vector.at(i).first << endl;
            currentHue+=17;
            rows++;
        }
    }

    model->setRowCount(rows);

    legend->setModel(model);
    legend->setColumnWidth(0,30);
    legend->resizeColumnToContents(1);
    legend->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(widget);
    splitter->addWidget(legend);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 2);
    layout->addWidget(splitter);
    resize(500,300);
    setLayout(layout);
}

PieDialog::~PieDialog()
{
    delete ui;
}
