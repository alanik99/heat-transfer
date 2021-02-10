#include <QVBoxLayout>
#include "widget.h"

Widget::Widget(QWidget *parent, const typeOfWidget t)
    : QWidget(parent)
{
    setWindowTitle("plot");
    setMinimumSize(450, 375);

    plot = new QCustomPlot;
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("u");
    //Ox Range
    plot->xAxis->setRange(0, 1);
    plot->xAxis->setAutoTickStep(false);
    plot->xAxis->setTickStep(0.1);

    if(t == GRID)
    {
        paintGraph(10, T_end/2, 0, "N = 10", Qt::blue);
        paintGraph(20, T_end/2, 1, "N = 20", Qt::red);
        paintGraph(100, T_end/2, 2, "N = 100", Qt::yellow);
        paintGraph(200, T_end/2, 3, "N = 200", Qt::green);

        plot->yAxis->setRange(600, 1600);

        title("Grid convergence for hx for t = T/2");
    }
    else if(t == TIMES)
    {
        picked_N = 100;

        paintGraph(picked_N, T_end/4, 0, "T_end/4", Qt::blue);
        paintGraph(picked_N, T_end/2, 1, "T_end/2", Qt::red);
        paintGraph(picked_N, 3*T_end/4, 2, "3T_end/4", Qt::yellow);
        paintGraph(picked_N, T_end, 3, "T_end", Qt::green);

        plot->yAxis->setRange(0, 3000);

        title("Times");
    }

    plot->legend->setVisible(true);
    plot->replot();

    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(plot);
    setLayout(l);
}

void Widget::setVectors(const double N, const double time)
{
    h = x_end/N;
    tau = h*h/2/a_t;

    t.clear();
    t = {t0};
    for (int i = 1; t[i-1] < T_end; ++i)
        t.push_back(t0 + tau*i);


    x.clear();
    x.resize(N+1);
    x[0] = x0;
    for (int i = 1; i < x.size(); ++i)
        x[i] = x[i-1] + h;


    u.clear();
    u.resize(N+1);
    for (int i = 0; i < u.size(); ++i)
        u[i] = 10;


    u1.clear();
    u1.resize(N+1);

    double t_size = t.size();
    double time1 = (t_size-1)/4, time2 = (t_size-1)/2, time3 = 3*(t_size-1)/4, time4 = (t_size-1);

    udef.clear();
    for (int i = 1; i < t_size; ++i) // iterate over rows
    {
        for (int j = 1; j < N; ++j) // calculate middle values inside one row
            u1[j] = u[j] + (a_t*tau/(h*h)) * (u[j+1] - 2*u[j] + u[j-1]);

        u1[N] = u1[N-1]; // right value

        u1[0] = (alpha*T_g + a_t*u1[1]/h) / (alpha + a_t/h); // left value

        u = u1;

        if(        (time == T_end/4 && i == time1)
                   || (time == T_end/2 && i == time2)
                   || (time == 3*T_end/4 && i == time3)
                   || (time == T_end && i == time4)        ) udef = u;
    }
}

void Widget::paintGraph(const double N, const double time,
             const int num, const QString& name, const QColor& colour)
{
    setVectors(N, time);
    plot->addGraph();
    plot->graph(num)->setName(name);
    plot->graph(num)->setData(x, udef);
    plot->graph(num)->setPen(QPen(colour));
}

void Widget::title(const QString& title)
{
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(plot, title));
}
