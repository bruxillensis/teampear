#include "tablayoutwidget.h"
#include "ui_tablayoutwidget.h"

tabLayoutWidget::tabLayoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabLayoutWidget)
{
    ui->setupUi(this);
}

tabLayoutWidget::~tabLayoutWidget()
{
    delete ui;
}



void tabLayoutWidget::on_filterDataButton_clicked()
{
filterDialog d;
d.setModal(true);
d.exec();
}
