#include "piechartwidget.h"
#include <QPainter>
#include <vector>
#include <QColor>
#include <iostream>

using namespace std;

PieChartWidget::PieChartWidget(QWidget *parent): QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *)
{
    int i, j, current, total = 0;
    QPainter painter(this);
    QRectF size = QRectF(10, 10, this->height()-10, this->height()-10);
    int currentHue = 0, last_slice = 0, current_slice;

    //get total number of pubs
    for(i = 0; i < data.size(); i++){
        for(j = 0 ; j < data.at(i).second.size(); j++){
            total += data.at(i).second.at(j).second;
        }
    }

    cout << total << endl;

    //gen pie slices
    for(i=0; i < data.size(); i++){
        current = 0;
        for(j = 0 ; j < data.at(i).second.size(); j++){
            current += data.at(i).second.at(j).second;
        }
        if(current > 0){
            QColor current_color;
            current_color.setHsv(currentHue,210,255);
            painter.setBrush(current_color);
            cout << current << endl;
            current_slice = ((double)current/total)*360;
            painter.drawPie(size, last_slice*16, current_slice*16);
            last_slice += current_slice;
            currentHue += 17;
        }
    }



}

void PieChartWidget::setData(std::vector<std::pair<std::string,std::vector<std::pair<std::string,int> > > > vector)
{
    data = vector;
    repaint();
    update();

}

