#pragma once
#include <vector>
#include <QColorDialog>
#include "point.h"
#include <windows.h>
#include <cmath>

class PixelSet{
public:
    PixelSet(){};
    ~PixelSet(){};

    void setID(int i);
    void setColor(QColor &color_);
    void add(int x, int y);
    void paint(QImage *image, int& xRangeMin, int& xRangeMax, int& yRangeMin, int& yRangeMax);
    void addRealPoint();

    int id;
    QColor color = Qt::black;
    std::vector<Point> points;

    int category = 0;
    double x1, y1, x2, y2;
    void SetLine(double x1_, double y1_, double x2_, double y2_);
};
