#include "drawPixelSet.h"

DrawPixelSet::DrawPixelSet(QWidget* parent)
    : QWidget(parent) {
    this->ui = new Ui::mainWnd;
    ui->setupUi(this);
    for (int i = 0; i < 1000000; i++)
    {
        d[i] = new float[6];
        d2[i] = new float[6];
    }
}

DrawPixelSet::~DrawPixelSet() {
    delete(this->ui);

    for (int i = 0; i < 1000000; i++)
    {
        delete[] d[i];
        delete[] d2[i];
    }
    delete[]d;
    delete[]d2;
}

void DrawPixelSet::Run() {
    clock_t startTime,endTime;
    startTime = clock();//计时开始
    QImage* image;
    image = new QImage(1280, 960, QImage::Format_RGB32);

    // 涂背景颜色
    QPainter* painter = new QPainter();
    painter->begin(image);
    painter->setPen(QPen(Qt::white, 1));
    painter->setBrush(QColor(Qt::white));
    painter->drawRect(0, 0, 1280, 960);
    painter->end();

    // 画水深点
    // 大地坐标转屏幕中心坐标系坐标
    for (int k = 0; k < depthQuantity; k++) {
        double psi = 90 * 3.14159 / 180;
        double cos_psi = std::cos(psi);
        double sin_psi = std::sin(psi);
        // 画面中心坐标系
        double temp = d[k][0];
        double temp1 = d[k][1];
        double x1s_ = d[k][0] * cos_psi + d[k][1] * sin_psi - X0 * cos_psi - Y0 * sin_psi;
        double y1s_ = d[k][1] * cos_psi - d[k][0] * sin_psi - Y0 * cos_psi + X0 * sin_psi;
        // 屏幕坐标
        double x1s = x1s_ / ratio + 640;
        double y1s = y1s_ / ratio + 480;

        this->d2[k][0] = x1s;
        this->d2[k][1] = y1s;
        this->d2[k][2] = d[k][2];
        this->d2[k][3] = d[k][3];
        this->d2[k][4] = d[k][4];
        this->d2[k][5] = d[k][5];
    }
    int space = depthQuantity / 1000 + 1;
    for (int kk = 0; kk < this->depthQuantity; kk+= space) {
        int xx = d2[kk][0];
        int yy = d2[kk][1];
        int xRangeMin = 0;
        int xRangeMax = 1280;
        int yRangeMin = 0;
        int yRangeMax = 960;
        if (xx > xRangeMin && xx < xRangeMax && yy > yRangeMin && yy < yRangeMax) {
            DrawNumber(image, d2[kk][2], d2[kk][3], d2[kk][4], d2[kk][5], d2[kk][0], d2[kk][1]);
        }
    }

    //// 画dxf
    // 真实坐标转画布坐标 高斯坐标转换
    double psi = 90 * 3.14159 / 180;
    double cos_psi = std::cos(psi);
    double sin_psi = std::sin(psi);
    for (int i = 0; i < pixelSetList.size(); i++) {
        pixelSetList[i].points.clear();
        // 画面中心坐标系
        double x1s_ = pixelSetList[i].x1 * cos_psi + pixelSetList[i].y1 * sin_psi - X0 * cos_psi - Y0 * sin_psi;
        double y1s_ = pixelSetList[i].y1 * cos_psi - pixelSetList[i].x1 * sin_psi - Y0 * cos_psi + X0 * sin_psi;
        double x2s_ = pixelSetList[i].x2 * cos_psi + pixelSetList[i].y2 * sin_psi - X0 * cos_psi - Y0 * sin_psi;
        double y2s_ = pixelSetList[i].y2 * cos_psi - pixelSetList[i].x2 * sin_psi - Y0 * cos_psi + X0 * sin_psi;
        // 屏幕坐标
        double x1s = x1s_ /  ratio + 640;
        double y1s = y1s_ / ratio + 480;
        double x2s = x2s_ / ratio + 640;
        double y2s = y2s_ / ratio + 480;

        // 点到线段的最短距离,判断该线段是否有部分进入画面
        double A = pixelSetList[i].y1 - pixelSetList[i].y2;
        double B = pixelSetList[i].x2 - pixelSetList[i].x1;
        double C = pixelSetList[i].x1 * pixelSetList[i].y2 - pixelSetList[i].x2 * pixelSetList[i].y1;
        double d0 = std::abs(A * X0 + B * Y0 + C) / std::sqrt(A * A + B * B);
        double d1 = std::sqrt((pixelSetList[i].x1 - X0) * (pixelSetList[i].x1 - X0) + (pixelSetList[i].y1 - Y0) * (pixelSetList[i].y1 - Y0));
        double d2 = std::sqrt((pixelSetList[i].x2 - X0) * (pixelSetList[i].x2 - X0) + (pixelSetList[i].y2 - Y0) * (pixelSetList[i].y2 - Y0));
        if (d0 < 1600 * ratio || d1 < 1600 * ratio || d2 < 1600 * ratio) {
            DrawLine_Bresenham(x1s, y1s, x2s, y2s, pixelSetList[i]);
            int xRangeMin = 0;
            int xRangeMax = 1280;
            int yRangeMin = 0;
            int yRangeMax = 960;
            pixelSetList[i].paint(image, xRangeMin, xRangeMax, yRangeMin, yRangeMax);
        }
    }

    QPixmap imagePixmap = QPixmap::fromImage(*image);
    ui->label->setPixmap(imagePixmap);

    endTime = clock();
    int spendTime = endTime - startTime;

    ui->label_2->setText(QString::number(spendTime));
}

void DrawPixelSet::LoadDxf() {
    std::ifstream infile;
    std::string file = "D:\\QT_temp\\Project3\\Project3\\out.txt";
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    std::string s;
    int pixelID = 0;
    while (std::getline(infile, s))
    {
        std::cout << s << std::endl;

        std::string::size_type pos1, pos2;
        std::string c = ",";    //分隔符
        std::vector<std::string> v;   //储存分割出的字符
        pos2 = s.find(c);
        pos1 = 0;
        while (std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2 - pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length())
            v.push_back(s.substr(pos1));
        
        PixelSet p;
        p.setID(pixelID);
        if (stringToNum<double>(v[0]) == 1) {
            p.SetLine(stringToNum<double>(v[2]), stringToNum<double>(v[1]), stringToNum<double>(v[4]), stringToNum<double>(v[3]));
        }
        pixelSetList.push_back(p);
        pixelID += 1;
    }
    infile.close();
}

void DrawPixelSet::LoadXyz() {
    std::ifstream infile;
    std::string file = "D:\\QT_temp\\Project3\\Project3\\depth.txt";
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    std::string s;
    int pixelID = 0;
    int i = 0;
    while (std::getline(infile, s))
    {
        std::cout << s << std::endl;
        std::string::size_type pos1, pos2;
        std::string c = ",";    //分隔符
        std::vector<std::string> v;   //储存分割出的字符
        pos2 = s.find(c);
        pos1 = 0;
        while (std::string::npos != pos2)
        {
            v.push_back(s.substr(pos1, pos2 - pos1));

            pos1 = pos2 + c.size();
            pos2 = s.find(c, pos1);
        }
        if (pos1 != s.length())
            v.push_back(s.substr(pos1));

        d[i][0] = stringToNum<double>(v[1]);
        d[i][1] = stringToNum<double>(v[0]);
        int temp = stringToNum<double>(v[2]) * 100;
        int temp1 = floor(temp / 1000);
        int temp2 = floor((temp - temp1 * 1000) / 100);
        int temp3 = floor((temp - temp1 * 1000 - temp2 * 100) / 10);
        int temp4 = floor((temp - temp1 * 1000 - temp2 * 100 - temp3 * 10) / 1);
        d[i][2] = temp1;
        d[i][3] = temp2;
        d[i][4] = temp3;
        d[i][5] = temp4;

        d2[i][0] = 0;
        d2[i][1] = 0;
        d2[i][2] = 0;
        d2[i][3] = 0;
        d2[i][4] = 0;
        d2[i][5] = 0;

        i += 1;
    }
    infile.close();
    depthQuantity = i;
}

void DrawPixelSet::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        middleBtnPress = true;
        middleBtnRelease = false;

        mouseLastX = event->globalX();
        mouseLastY = event->globalY();
        
    }
}

void DrawPixelSet::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        middleBtnPress = false;
        middleBtnRelease = true;

        Run();
    }
}

void DrawPixelSet::mouseMoveEvent(QMouseEvent* event) {
    if (middleBtnPress && !middleBtnRelease) {
        this->mouseCurrentX = event->globalX();
        this->mouseCurrentY = event->globalY();
        this->X0 += (this->mouseCurrentY - this->mouseLastY) * ratio;
        this->Y0 -= (this->mouseCurrentX - this->mouseLastX) * ratio;
        this->mouseLastX = mouseCurrentX;
        this->mouseLastY = mouseCurrentY;
        int temp = 0;
    }
}

void DrawPixelSet::wheelEvent(QWheelEvent* event) {
    double oneloop = event->delta() / 120;//转一圈化成单位1
    if (event->delta() > 0) {//前滚
        this->ratio -= oneloop * this->ratio / 10;
    }
    else {//当滚轮向使用者方向旋转时
        this->ratio -= oneloop * this->ratio / 10;
    }
    Run();
}
