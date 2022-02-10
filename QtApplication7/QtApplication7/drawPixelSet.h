#pragma once
#include "ui_drawPixelSet.h"
#include "algorithm.h"
#include "pixelSet.h"
#include <QWidget>
#include <QPainter>
#include <windows.h>
#include <vector>
#include <ctime>
#include <QMouseEvent>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>

template <class Type>
Type stringToNum(const std::string& str)
{
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

class DrawPixelSet : public QWidget {
	Q_OBJECT
public:
	DrawPixelSet(QWidget* parent = nullptr);
	~DrawPixelSet();
	void Run();
	void LoadDxf();
	void LoadXyz();

	int depthQuantity = 0;
	float** d = new float* [1000000];
	float** d2 = new float* [1000000];

	// X0 Y0为屏幕坐标系，原点在屏幕中心 屏幕分辨率1280*960
	// 大地坐标系为 北为X正，东为Y正
	// 屏幕坐标左上角为原点 向右X正，向下Y正
	double X0 = 3862000;
	double Y0 = 484000;
	double ratio = 100;//1个像素表示ratio米

	int mouseLastX = 0;
	int mouseLastY = 0;
	int mouseCurrentX = 0;
	int mouseCurrentY = 0;
	bool middleBtnPress = false;
	bool middleBtnRelease = true;

private:
	Ui::mainWnd* ui;
	
	std::vector<PixelSet> pixelSetList;

	void mousePressEvent(QMouseEvent* event);        //单击

	void mouseReleaseEvent(QMouseEvent* event);      //释放

	//void mouseDoubleClickEvent(QMouseEvent* event);  //双击

	void mouseMoveEvent(QMouseEvent* event);         //移动

	void wheelEvent(QWheelEvent* event);             //滑轮
};