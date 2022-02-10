#include "algorithm.h"

//��һ��ֱ��-Bresenham�㷨
void DrawLine_Bresenham(int x1, int y1, int x2, int y2, PixelSet& myset)
{
    int xl = x1; int yl = y1;//(xl,yl)��ʾλ�����ĵ�(x_left)
    int xr = x2; int yr = y2;//(xr,yr)��ʾλ���Ҳ�ĵ�(x_right)
    if (x1 > x2) { //ȷ�����ҵ��Ӧ(xl,yl)��(xr,yr)
        xl = x2; yl = y2;
        xr = x1; yr = y1;
    }

    bool flag = true;//���λ���ҵ����·���б�ʴ��ڵ���0�������ʱΪtrue������Ϊ��
    if (yl > yr) flag = false;

    /* �Ƚ���������������ˮƽ����ֱ���Խ��� */
    //��ֱ��
    if (xl == xr) {
        int di = -1;
        if (flag) di = 1; //���λ���ҵ��·�ʱ
        for (int i = yl; i != yr; i += di) {
            myset.add(xl, i);
        }
        myset.add(xr, yr);
        return;
    }
    //ˮƽ��
    if (yl == yr) {
        for (int i = xl; i <= xr; ++i) {
            myset.add(i, yl);
        }
        return;
    }
    //�Խ���1
    if ((xr - xl) == (yr - yl)) {
        for (int i = xl, j = yl; i <= xr; ++i, ++j) {
            myset.add(i, j);
        }
        return;
    }
    //�Խ���2
    if ((xr - xl) == -(yr - yl)) {
        for (int i = xl, j = yl; i <= xr; ++i, --j) {
            myset.add(i, j);
        }
        return;
    }

    /* ���������������������ۣ���ȷ�������ҵ㣬����ֻ����������ˣ� */
    int xk, yk;
    int dx, dy;
    int p; //Bresenham�����㷨�е�k���ľ��߲���

    xk = xl; yk = yl;
    dx = xr - xl;
    dy = yr - yl;

    if (flag) { //б�ʴ���0�����
        if (dy < dx) { //б��С��1
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
        else { //б�ʴ���1
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
    else { //б��С��0�����
        if (-dy < dx) { //б�ʴ���-1
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
        else { //б��С��-1
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
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //�к�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        case 5:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //�º�
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //�к�
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        case 6:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //�º�
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //�к�
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        case 7:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        case 8:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //�º�
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //�к�
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        case 9:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y - 6, RGB(255, 0, 0)); //�к�
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 5; j++) {
                image->setPixel(x - 10, y - 5 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //������
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //������
            }
            break;
        default:
            for (int i = 0; i < 8; i++) {
                image->setPixel(x - 17 + i, y, RGB(255, 0, 0)); //�º�
                image->setPixel(x - 17 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
            }
            for (int j = 0; j < 11; j++) {
                image->setPixel(x - 10, y - 11 + j, RGB(255, 0, 0)); //����
                image->setPixel(x - 17, y - 11 + j, RGB(255, 0, 0)); //����
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
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //�к�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //�º�
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //�к�
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //�º�
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //�к�
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //�º�
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //�к�
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y - 6, RGB(255, 0, 0)); //�к�
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x - 1, y - 5 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //������
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //������
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x - 8 + i, y, RGB(255, 0, 0)); //�º�
            image->setPixel(x - 8 + i, y - 12, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x - 1, y - 11 + j, RGB(255, 0, 0)); //����
            image->setPixel(x - 8, y - 11 + j, RGB(255, 0, 0)); //����
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
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //�к�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 8, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 1 + i, y + 3 , RGB(255, 0, 0)); //�º�
            image->setPixel(x + 1 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x + 8, y - 8 + j, RGB(255, 0, 0)); //����
            image->setPixel(x + 1, y - 8 + j, RGB(255, 0, 0)); //����
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
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //�к�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 5:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 6:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 7:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 8:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    case 9:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y - 3, RGB(255, 0, 0)); //�к�
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 5; j++) {
            image->setPixel(x + 17, y - 2 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //������
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //������
        }
        break;
    default:
        for (int i = 0; i < 8; i++) {
            image->setPixel(x + 10 + i, y + 3, RGB(255, 0, 0)); //�º�
            image->setPixel(x + 10 + i, y - 9, RGB(255, 0, 0)); //�Ϻ�
        }
        for (int j = 0; j < 11; j++) {
            image->setPixel(x + 17, y - 8 + j, RGB(255, 0, 0)); //����
            image->setPixel(x + 10, y - 8 + j, RGB(255, 0, 0)); //����
        }
        break;
    }
}
