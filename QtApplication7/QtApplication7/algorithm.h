#pragma once
#include "pixelSet.h"
#include <vector>
#include <QWidget>

void DrawLine_Bresenham(int x1, int y1, int x2, int y2, PixelSet& pixelSet);

void DrawNumber(QImage* image, const int& first, const int& second, const int& third, const int& forth, const int& x, const int& y);
