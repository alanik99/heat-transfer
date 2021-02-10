#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum typeOfWidget {GRID_H, GRID_TAU, TIMES};

    Widget(QWidget *parent = nullptr, const typeOfWidget t = GRID_H);

private:
    QVector<double> t{}, x{}, u{}, udef{};

    const double a_t = 1, alpha = 1, T_g = 3000;

    const double t0 = 0, T_end = 1;
    double h, tau;
    int picked_N;
    double picked_tau;

    const double x0 = 0, x_end = 1;

    const double A = 1, C = 1;
    double B;
    QVector<double> k{}, l{}, D{};

    QCustomPlot* plot;

    void setVectors(const double Tau, const double N, const double time);
    void paintGraph(const double Tau, const double N, const double time,
                 const int num, const QString& name, const QColor& colour);
    void title(const QString& title);
};
#endif // WIDGET_H
