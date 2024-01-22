#include "controlwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ControlWindow w;
    w.show();
    return app.exec();
}
