#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QObject>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>

#include "vaccum.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Create a main window
    QMainWindow mainWindow;

    // Create a central widget for the main window
    QWidget *centralWidget = new QWidget(&mainWindow);

    // Create a layout for the central widget
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create a QwtPlot widget
    QwtPlot *plot = new QwtPlot(centralWidget);
    plot->setCanvasBackground(Qt::white);
    layout->addWidget(plot);

    // Set the range and scale of the x-axis
    plot->setAxisScale(QwtPlot::xBottom, 0, 100, 50);

    // Set the range and scale of the y-axis
    plot->setAxisScale(QwtPlot::yLeft, 0, 50, 1);

    // Redraw the plot with the updated axis limits
    plot->replot();

    // Create a curve to be plotted
    QwtPlotCurve *curve = new QwtPlotCurve("Vaccum Curve");

  //  qDebug()<<win.periodms;

    // Attach the curve to the plot
    curve->attach(plot);

    // Create an object to handle dynamic updates of the plot
    Vaccum vaccum(curve, plot);

    // Set up the main window
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setGeometry(100, 100, 800, 600);
    mainWindow.show();

    // Enter the application main loop
    return app.exec();
}


