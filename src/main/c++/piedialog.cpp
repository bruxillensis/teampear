#include "piedialog.h"
#include "ui_piedialog.h"
#include "piechartwidget.h"
#include <QGridLayout>

PieDialog::PieDialog(QWidget *parent, std::vector<std::pair<std::string,std::vector<std::pair<std::string,int> > > > vector) :
    QDialog(parent),
    ui(new Ui::PieDialog)
{
    ui->setupUi(this);
    PieChartWidget *widget = new PieChartWidget();
    widget->setData(vector);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(widget);
    setLayout(layout);
}

PieDialog::~PieDialog()
{
    delete ui;
}
