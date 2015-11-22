#include "filterdialog.h"
#include "ui_filterdialog.h"

filterDialog::filterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filterDialog)
{
    ui->setupUi(this);

    //none of the filters are checked at first
    dateFilterChecked = false;
    domainFilterChecked = false;
    hourFilterChecked = false;
    FundingFilterChecked = false;
    countFilterChecked = false;

    //set initial values for user input variables
    startingDate = QDate(); //constructs a null date, null dates are invalid
    endDate = QDate();
    domainSelected = "";
    startingAmount = 0;
    endAmount = 0;
    startingHours = 0;
    endHours = 0;
    startingCount = 0;
    endCount = 0;

}

filterDialog::~filterDialog()
{
    delete ui;
}

void filterDialog::on_filterDoneButton_clicked()
{

this->accept();
}

void filterDialog::on_dateCheckBox_clicked(bool checked)
{
    dateFilterChecked = checked;

}

void filterDialog::on_domainCheckBox_clicked(bool checked)
{
    domainFilterChecked = checked;
}

void filterDialog::on_fundingCheckBox_clicked(bool checked)
{
    FundingFilterChecked = checked;
}

void filterDialog::on_hourCheckBox_clicked(bool checked)
{
    hourFilterChecked = checked;
}

void filterDialog::on_countCheckBox_clicked(bool checked)
{
    countFilterChecked = checked;
}

void filterDialog::on_startDateEdit_editingFinished()
{

startingDate = ui->startDateEdit->date();
}

void filterDialog::on_endDateEdit_editingFinished()
{
endDate = ui->endDateEdit->date();
}

void filterDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
domainSelected = arg1;
}

void filterDialog::on_startDoubleSpinBox_valueChanged(double arg1)
{
startingAmount = arg1;
}

void filterDialog::on_endDoubleSpinBox_valueChanged(double arg1)
{
endAmount = arg1;
}

void filterDialog::on_startHourSpinBox_valueChanged(int arg1)
{
startingHours = arg1;
}

void filterDialog::on_endHourSpinBox_valueChanged(int arg1)
{
endHours = arg1;
}

void filterDialog::on_startCountSpinBox_valueChanged(int arg1)
{
    startingCount = arg1;
}

void filterDialog::on_endCountSpinBox_valueChanged(int arg1)
{
endCount = arg1;
}

QDate filterDialog::getStartDate(){

    return startingDate;
}

QDate filterDialog::getEndDate(){

    return endDate;
}

QString filterDialog::getDomain(){
    return domainSelected;
}

long double filterDialog::getStartAmount(){
    return startingAmount;
}

long double filterDialog::getEndAmount(){
 return endAmount;
}

long int filterDialog::getStartHours(){
    return startingHours;
}

long int filterDialog::getEndHours(){
    return endAmount;
}

long int filterDialog::getStartCount(){
    return startingCount;
}

long int filterDialog::getEndCount(){
    return endCount;
}
