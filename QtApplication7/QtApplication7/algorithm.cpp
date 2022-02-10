#include "algorithm.h"

//画一条直线-Bresenham算法
void DrawLine_Bresenham(int x1, int y1, int x2, int y2, PixelSet& myset)
{
    int xl = x1; int yl = y1;//(xl,yl)表示位于左侧的点(x_left)
    int xr = x2; int yr = y2;//(xr,yr)表示位于右侧的点(x_right)
    if (x1 > x2) { //确保左、右点对应(xl,yl)、(xr,yr)
        xl = x2; yl = y2;
        xr = x1; yr = y1;
    }

    bool flag = true;//左点位于右点左下方（斜率大于等于0的情况）时为true，否则为假
    if (yl > yr) flag = false;

    /* 先解决三种特殊情况：水平、垂直、对角线 */
    //垂直线
    if (xl == xr) {
        int di = -1;
        if (flag) di = 1; //左点位于右点下方时
        for (int i = yl; i != yr; i += di) {
            myset.add(xl, i);
        }
        myset.add(xr, yr);
        return;
    }
    //水平线
    if (yl == yr) {
        for (int i = xl; i <= xr; ++i) {
            myset.add(i, yl);
        }
        return;
    }
    //对角线1
    if ((xr - xl) == (yr - yl)) {
        for (int i = xl, j = yl; i <= xr; ++i, ++j) {
            myset.add(i, j);
        }
        return;
    }
    //对角线2
    if ((xr - xl) == -(yr - yl)) {
        for (int i = xl, j = yl; i <= xr; ++i, --j) {
            myset.add(i, j);
        }
        return;
    }

    /* 下面是针对四类情况的讨论（已确保了左、右点，所以只有四种情况了） */
    int xk, yk;
    int dx, dy;
    int p; //Bresenham画线算法中第k步的决策参数

    xk = xl; yk = yl;
    dx = xr - xl;
    dy = yr - yl;

    if (flag) { //斜率大于0的情况
        if (dy < dx) { //斜率小于1
            p = 2 * dy - dx;
            while (xk <= xr) {
                myset.add(xk, yk);
                if (p >= 0) {
                    yk++;
                    p += 2 * (dy - dx);
                }
                else {
                    p += 2 * dy;
                }
                xk++;
            }
        }
        else { //斜率大于1
            p = 2 * dx - dy;
            while (yk <= yr) {
                myset.add(xk, yk);
                if (p >= 0) {
                    xk++;
                    p += 2 * (dx - dy);
                }
                else {
                    p += 2 * dx;
                }
                yk++;
            }
        }
    }
    else { //斜率小于0的情况
        if (-dy < dx) { //斜率大于-1
            p = 2 * dy + dx;
            while (xk <= xr) {
                myset.add(xk, yk);
                if (p <= 0) {
                    yk--;
                    p += 2 * (dy + dx);
                }
                else {
                    p += 2 * dy;
                }
                xk++;
            }
        }
        else { //斜率小于-1
            p = -2 * dx - dy;
            while (yk >= yr) {
                myset.add(xk, yk);
                if (p <= 0) {
                    xk++;
                    p += 2 * (-dx - dy);
                }
                else {
                    p += 2 * (-dx);
                }
                yk--;
            }
        }
    }
}

void DrawNumber(QImage* image, const int& first, const int& second, const int& third, const int& forth, const int& x, const int& y) {
    switch (first) {       
        case 1:
            for (int j = 0; j < 13; j++) {
                image->setPixel(x - 10, y - 12 + j, RGB(255, 0, 0));
            }
            break;
        case 2:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0));
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0));
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0));
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 17, y - 5 + j, RGB(255, 0, 0));
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0));
            }
            break;
        case 3:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0));
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0));
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0));
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0));
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0));
            }
            break;
        case 4:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //中横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //右上竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左上竖
            }
            break;
        case 5:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //下横
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //中横
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左上竖
            }
            break;
        case 6:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //下横
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //中横
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 17, y - 5 + j, RGB(255, 0, 0)); //左下竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左上竖
            }
            break;
        case 7:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //右上竖
            }
            break;
        case 8:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //下横
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //中横
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //右上竖
                image->setPixel(x - 17, y - 5 + j, RGB(255, 0, 0)); //左下竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左上竖
            }
            break;
        case 9:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //中横
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //右下竖
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //右上竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左上竖
            }
            break;
        default:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //下横
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //上横
            }
            for (int j = 0; j < 11; j++) {
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //右竖
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //左竖
            }
            break;
    }
    switch (second) {
    case 1:
        for (int j = 0; j < 13; j++) {
            image->setPixel(x - 1, y - 12 + j, RGB(255, 0, 0));
        }
        break;
    case 2:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0));
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0));
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 8, y - 5 + j, RGB(255, 0, 0));
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0));
        }
        break;
    case 3:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0));
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0));
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0));
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0));
        }
        break;
    case 4:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //中横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //下横
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //中横
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //下横
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //中横
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 8, y - 5 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //右上竖
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //下横
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //中横
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x - 8, y - 5 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //中横
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //下横
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //右竖
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //左竖
        }
        break;
    }
    switch (third) {
    case 1:
        for (int j = 0; j < 13; j++) {
            image->setPixel(x + 1, y - 9 + j, RGB(255, 0, 0));
        }
        break;
    case 2:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0));
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0));
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 1, y - 2 + j, RGB(255, 0, 0));
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0));
        }
        break;
    case 3:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0));
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0));
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0));
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0));
        }
        break;
    case 4:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //中横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 1, y - 2 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //右上竖
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 1, y - 2 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3 , RGB(255, 0, 0)); //下横
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //右竖
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //左竖
        }
        break;
    }
    switch (forth) {
    case 1:
        for (int j = 0; j < 13; j++) {
            image->setPixel(x + 17, y - 9 + j, RGB(255, 0, 0));
        }
        break;
    case 2:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0));
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0));
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 10, y - 2 + j, RGB(255, 0, 0));
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0));
        }
        break;
    case 3:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0));
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0));
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0));
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0));
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0));
        }
        break;
    case 4:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //中横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 10, y - 2 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //右上竖
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 10, y - 2 + j, RGB(255, 0, 0)); //左下竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //中横
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //右下竖
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //右上竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左上竖
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //下横
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //上横
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //右竖
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //左竖
        }
        break;
    }
}
