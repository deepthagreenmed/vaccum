#ifndef VACCUM_H
#define VACCUM_H

#include <QObject>
#include <QVector>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class Vaccum : public QObject
{
    Q_OBJECT
public:
    Vaccum(QwtPlotCurve *curve, QwtPlot *plot);
    ~Vaccum();
    float convert();
    float stabilize();

private slots:
    void updatePlot();

private:
    QwtPlotCurve *curve;
    QwtPlot *plot;
    QTimer *timer;
    int spi_fd;

};

#endif // VACCUM_H
