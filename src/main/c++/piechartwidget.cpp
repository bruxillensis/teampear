#include "piechartwidget.h"
#include <QPainter>
#include <vector>
#include <QColor>
#include <iostream>
#include "node.h"

#define HUE_MAX		359			//maximum HSV value
#define PIE_MULT	16			//Pie slice multiplier
#define C_SAT		210			//Pie slice saturation
#define C_VAL		255			//Pie slice lightness
#define DEGREES		360			//multiplier to convert pie slices to degrees
#define EDGE		10			//white space between pie chart and edge of window

using namespace std;

PieChartWidget::PieChartWidget(QWidget *parent): QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *)
{
    int i, current, total;
    QPainter painter(this);
    QRectF size = QRectF(EDGE, EDGE, this->width()-EDGE, this->width()-EDGE);
    int currentHue = 0, last_slice = 0, current_slice;

	//check if csv data is of grants and clinical funding type
	bool money = false;
	if (data->getFourth() > 0)
		money = true;

	QColor color;

	vector<node*> *children = data->getChildren();

    //get total for pie chart
	total = data->getSecond();
	
	//color increment
	int c_inc = HUE_MAX / children->size();

    //for loop to gen pie slices
    for(i=0; i < children->size(); i++){
		//get current pie slice size
		current = children->at(i)->getSecond();
        if(current > 0){
	
            color.setHsv(currentHue,C_SAT,C_VAL);						//gen new color
            painter.setBrush(color);									//set brush as new color
            current_slice = ((double)current/total)*DEGREES;					//generate slice
            painter.drawPie(size, last_slice*PIE_MULT, current_slice*PIE_MULT);	//draw slice

            last_slice += current_slice;		//increment tracker of last slice place

            currentHue += c_inc;				//increment hue
        }
    }



}

//method sends the data to the piechart and redraws chart
//@Param root: root node to draw pie chart from
void PieChartWidget::setData(node* root)
{
	//sets the private variable data to root
    data = root;

	//repaints the pie chart
    repaint();

	//updates the visual of the new pie chart
    update();

}

