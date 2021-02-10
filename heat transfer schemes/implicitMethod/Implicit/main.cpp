#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget grid_h(nullptr, Widget::GRID_H);
    grid_h.show();

    Widget grid_tau(nullptr, Widget::GRID_TAU);
    grid_tau.show();

    Widget times(nullptr, Widget::TIMES);
    times.show();

    return a.exec();
}
