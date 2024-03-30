#ifndef GPSHARP_HPP
#define GPSHARP_HPP

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <math.h>


#define SPI_DEVICE "/dev/spidev0.0" // SPI device file
#define SPI_MODE SPI_MODE_0
#define SPI_SPEED 1000000 // clock speed SPI 1MHz
#define NUM_SAMPLE 25

extern int spi_fd;

int spi_init(const char* device);
int read_adc_channel(int channel);
int median(int a[], int size);

void spi_close();
double adc_to_distance(int adc_value);



#endif // GPSHARP_H
