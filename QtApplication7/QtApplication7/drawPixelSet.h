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

	// X0 Y0Ϊ��Ļ����ϵ��ԭ������Ļ���� ��Ļ�ֱ���1280*960
	// �������ϵΪ ��ΪX������ΪY��
	// ��Ļ�������Ͻ�Ϊԭ�� ����X��������Y��
	double X0 = 3862000;
	double Y0 = 484000;
	double ratio = 100;//1�����ر�ʾratio��

	int mouseLastX = 0;
	int mouseLastY = 0;
	int mouseCurrentX = 0;
	int mouseCurrentY = 0;
	bool middleBtnPress = false;
	bool middleBtnRelease = true;

private:
	Ui::mainWnd* ui;
	
	std::vector<PixelSet> pixelSetList;

	void mousePressEvent(QMouseEvent* event);        //����

	void mouseReleaseEvent(QMouseEvent* event);      //�ͷ�

	//void mouseDoubleClickEvent(QMouseEvent* event);  //˫��

	void mouseMoveEvent(QMouseEvent* event);         //�ƶ�

	void wheelEvent(QWheelEvent* event);             //����
};