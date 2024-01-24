#include "vaccum.h"

#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QProcess>
#include <stdint.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <vector>
#include <iostream>
Vaccum::Vaccum()
{
    initSPI();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(stabilize()));
    timer->start(30); // milliseconds
}

void Vaccum::initSPI()
{
    spi_fd = open("/dev/spidev2.0", O_RDWR);

    int mode;
    int bits = 8;
    int speed = 1000000;
    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
}

Vaccum::~Vaccum()
{
    close(spi_fd);
}

float Vaccum::stabilize()
{
    int sum = 0;
    for(int i=0; i<10; i++)
    {
        sum += (int)convert(0xD7);
    }
  // qDebug()<<"Vaccum"<<sum/10.0;
    return sum;

}

float Vaccum::convert(uint8_t channel)
{
    uint8_t tx[2];
    tx[0]=channel;
    tx[1]=0x00;
//    qDebug()<<tx[0]<<tx[1];

//    uint8_t tx[2]={0xD7,0x00};
    uint8_t rx[2] = {0x00, 0x00};
    uint16_t sample = 0;
    uint16_t delay = 0;
    uint8_t bits = 8;
    uint32_t speed = 1000000;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 2,
        .speed_hz = speed,
        .delay_usecs = delay,
        .bits_per_word = bits,
    };

    /* send the cmd to start the conversion and read the result */
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    qDebug()<<rx[0]<<rx[1];
//    rx[1] = 0x1F;
//    rx[0] = 0xFF;
    //sample =  rx[0] | (uint16_t)((rx[1] << 8) & 0x0fff) ;
    //float pressure = 1.0 * ((sample - OUTPUT_MIN) * (PRESSURE_MAX - PRESSURE_MIN) / (OUTPUT_MAX - OUTPUT_MIN) + PRESSURE_MIN);


 //   qDebug()<<sample;
    //qDebug()<<pressure;
    return sample;
}
