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

    int i, current, total = 0;
    QPainter painter(this);
    QRectF size = QRectF(10, 10, this->width()-10, this->width()-10);
    int currentHue = 0, last_slice = 0, current_slice;
    std::vector< std::pair< std::string, QColor>> legendVec;

    //get total number of pubs
    for(i = 0; i < data.size(); i++){
        total += static_cast<int>(data.at(i).second.size());
    }

    cout << total << endl;

    //gen pie slices
    for(i=0; i < data.size(); i++){
        QColor current_color;
        current_color.setHsv(currentHue,255,127);
        painter.setBrush(current_color);
        current = static_cast<int>(data.at(i).second.size());
        cout << current << endl;
        current_slice = ((double)current/total)*360;
        painter.drawPie(size, last_slice*16, current_slice*16);
        last_slice += current_slice;
        currentHue += 17;
        std::pair< std::string, QColor> cur_legend;
        cur_legend.first = data.at(i).first;
        cur_legend.second = current_color;
        legendVec.push_back(cur_legend);
    }


}

void PieChartWidget::setData(std::vector<std::pair<std::string,std::vector<std::pair<std::string,std::string> > > > vector)
{
    data = vector;
    repaint();
    update();
}

