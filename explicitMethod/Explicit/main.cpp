#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget grid(nullptr, Widget::GRID);
    grid.show();

    Widget times(nullptr, Widget::TIMES);
    times.show();

    return a.exec();
}
