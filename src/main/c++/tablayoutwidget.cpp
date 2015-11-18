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


//starting date
void tabLayoutWidget::on_dateEdit_dateChanged(const QDate &date)
{
ui->dateEdit->setDate(date);
starting = ui->dateEdit->date();
}

//ending date
void tabLayoutWidget::on_dateEdit_2_dateChanged(const QDate &date)
{
ui->dateEdit_2->setDate(date);
ending = ui->dateEdit->date();
}
