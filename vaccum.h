#ifndef VACCUM_H
#define VACCUM_H

#include <QObject>
#include <QVector>

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>

class Vaccum : public QObject
{
    Q_OBJECT
public:
    Vaccum();
    ~Vaccum();
    float convert();
    float stabilize();

private:
    int spi_fd;

};

#endif // VACCUM_H
