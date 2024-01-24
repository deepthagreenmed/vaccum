#ifndef VACCUM_H
#define VACCUM_H

#include <QObject>
#include <QVector>
#include <QTimer>

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>

class Vaccum : public QObject
{
    Q_OBJECT
public:
    Vaccum();
    ~Vaccum();
    float convert(uint8_t Channel );
    void initSPI();

private slots:
    float stabilize();

private:
    QTimer *timer;
    int spi_fd;

};

#endif // VACCUM_H
