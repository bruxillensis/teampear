#ifndef TABLAYOUTWIDGET_H
#define TABLAYOUTWIDGET_H

#include <QWidget>
#include <QDateEdit>
#include <QDateTimeEdit>

namespace Ui {
class tabLayoutWidget;
}

class tabLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tabLayoutWidget(QWidget *parent = 0);
    ~tabLayoutWidget();

private slots:
    void on_dateEdit_dateChanged(const QDate &date);

    void on_dateEdit_2_dateChanged(const QDate &date);

private:
    Ui::tabLayoutWidget *ui;
    QDate starting, ending;
};

#endif // TABLAYOUTWIDGET_H
