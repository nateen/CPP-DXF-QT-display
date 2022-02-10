#include "pixelSet.h"


void PixelSet::setID(int i){
    this->id = i;
}

void PixelSet::setColor(QColor &color_){
    this->color = color_;
}

void PixelSet::add(int x, int y){
    this->points.push_back(Point(x, y));
}

void PixelSet::paint(QImage *image, int& xRangeMin, int& xRangeMax, int& yRangeMin, int& yRangeMax){
    for(Point point: points){
        if (point.x > xRangeMin && point.x < xRangeMax && point.y > yRangeMin && point.y < yRangeMax) {
            image->setPixel(point.x, point.y, RGB(0, 0, 0));
        }
    }
}

void PixelSet::SetLine(double x1_, double y1_, double x2_, double y2_) {
    x1 = x1_;
    y1 = y1_;
    x2 = x2_;
    y2 = y2_;
}
