#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QDate>
#include <QString>
namespace Ui {
class filterDialog;
}

class filterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit filterDialog(QWidget *parent = 0);

    //getter methods for user input
    QDate getStartDate();
    QDate getEndDate();
    QString getDomain();
    long double getStartAmount();
    long double getEndAmount();
    long float getStartHours();
	long float getEndHours();
    long int getStartCount();
    long int getEndCount();
	bool isDateChecked();
	bool isDomainChecked();
	bool isFundingChecked();
	bool isHoursChecked();
	bool isCountChecked();

    ~filterDialog();

private slots:
    void on_filterDoneButton_clicked();

    void on_dateCheckBox_clicked(bool checked);

    void on_domainCheckBox_clicked(bool checked);

    void on_fundingCheckBox_clicked(bool checked);

    void on_hourCheckBox_clicked(bool checked);

    void on_countCheckBox_clicked(bool checked);

   // void on_startDateEdit_editingFinished();

    //void on_endDateEdit_editingFinished();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_startDoubleSpinBox_valueChanged(double arg1);

    void on_endDoubleSpinBox_valueChanged(double arg1);

    void on_startHourSpinBox_valueChanged(int arg1);

    void on_endHourSpinBox_valueChanged(int arg1);

    void on_startCountSpinBox_valueChanged(int arg1);

    void on_endCountSpinBox_valueChanged(int arg1);

    void on_startDateEdit_dateChanged(const QDate &date);

    void on_endDateEdit_dateChanged(const QDate &date);

private:
    Ui::filterDialog *ui;

    //keeping track of which filters are chosen
bool dateFilterChecked, domainFilterChecked, hourFilterChecked, FundingFilterChecked, countFilterChecked;

    //keeping track of the user input
QDate startingDate, endDate;
QString domainSelected;
long double startingAmount,endAmount;
long float startingHours, endHours;
long int startingCount, endCount;
};

#endif // FILTERDIALOG_H
