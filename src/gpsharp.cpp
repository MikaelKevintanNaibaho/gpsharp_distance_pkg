#include "gpsharp_distance/gpsharp.hpp"

int spi_fd;

int spi_init(const char* device)
{
    spi_fd = open(device, O_RDWR);
    if (spi_fd < 0) {
        perror("error opening SPI device\n");
        return -1;
    }

    //set SPI_MODE
    int mode = SPI_MODE;
    if(ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) == -1) {
        perror("Error setting SPI mode\n");
        return -1;
    }

    //set SPI speed
    int speed = SPI_SPEED;
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        perror("error setting SPI speed");
        return -1;
    }

    return 0;
}

void spi_close()
{
    close(spi_fd);
}

int read_adc_channel(int channel)
{
    unsigned char tx_buf[3], rx_buf[3];
    int adc_value;

    //MCP3008 format untu single-ended input
    tx_buf[0] = 0x01;
    tx_buf[1] = (8 + channel) << 4;
    tx_buf[2] = 0x00;

    struct spi_ioc_transfer spi_transfer = {
        spi_transfer.tx_buf = (unsigned long)tx_buf,
        spi_transfer.rx_buf = (unsigned long)rx_buf,
        spi_transfer.len = 3,
        spi_transfer.speed_hz = SPI_SPEED,
        spi_transfer.delay_usecs = 0,
        spi_transfer.bits_per_word = 8,
    };

    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi_transfer) < 0) {
        perror("error reading ADC");
        return -1;
    }
    

    //extract adc value from recieved bytes
    adc_value = ((rx_buf[1] & 3) << 8) + rx_buf[2];
    return adc_value;
}

int median(int a[], int size)
{
    //sort array 
    for(int i = 0; i < (size-1); i++){
        for(int j = 0; j < (size-i-1); j++){
            if(a[j] > a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    //calculate median base on size
    if ( size % 2 == 0) {
        return (a[size/2 - 1] + a[size/2]) / 2;
    } else {
        return a[size/2];
    }
}

double adc_to_distance(int adc_value)
{
    // Convert ADC value to voltage (assuming 10-bit ADC and 5V reference)
    double voltage = (double)adc_value * (3.3 / 1023.0);

    // Calculate distance using the provided formula
    double distance = 27.127 * pow(voltage, -1.173);
    return distance;
}
