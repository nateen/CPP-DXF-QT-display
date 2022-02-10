#include "drawPixelSet.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DrawPixelSet w;
    w.LoadDxf();
    w.LoadXyz();
    w.Run();
    w.show();

    return a.exec();
}