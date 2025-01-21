/**
 * @file spi.h
 * @author Purinda Gunasekara <purinda@gmail.com>
 *
 * Created on 24 June 2012, 11:00 AM
 *
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_SPIDEV_SPI_H_
#define RF24_UTILITY_SPIDEV_SPI_H_

#include <stdint.h>
#include <stdexcept>

#ifndef RF24_SPI_SPEED
    #define RF24_SPI_SPEED 10000000
#endif

/** Specific exception for SPI errors */
class SPIException : public std::runtime_error
{
public:
    explicit SPIException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

class SPI
{

public:

    char* my_device0 = "/dev/spidev0.0";
    char* my_device1 = "/dev/spidev1.0";

    //void setDevice(char* device, int n){}
    
    bool myBegin(int busNo, uint32_t spi_speed = RF24_SPI_SPEED){

    if (this->spiIsInitialized) {
            return;
        }

        /* set spidev accordingly to busNo like:
         * busNo = 23 -> /dev/spidev2.3
         *
         * a bit messy but simple
         * */
        //char device[] = "/dev/spidev0.0";
        //device[11] += (busNo / 10) % 10;
        //device[13] += busNo % 10;

        //if busNo

        if (this->fd >= 0) // check whether spi is already open
        {
            close(this->fd);
            this->fd = -1;
        }

        this->fd = open(device, O_RDWR);
        if (this->fd < 0) {
            std::string msg = "[SPI::begin] Can't open device ";
            msg += device;
            msg += "; ";
            msg += strerror(errno);
            throw SPIException(msg);
        }

        this->spiIsInitialized = true;
        init(spi_speed);        
    }

    SPI();

    void begin(int busNo, uint32_t spi_speed = RF24_SPI_SPEED);

    uint8_t transfer(uint8_t tx);

    void transfernb(char* tbuf, char* rbuf, uint32_t len);

    void transfern(char* buf, uint32_t len);

    ~SPI();

private:
    int fd;
    uint32_t _spi_speed;
    bool spiIsInitialized = false;
    void init(uint32_t spi_speed = RF24_SPI_SPEED);
};

#endif // RF24_UTILITY_SPIDEV_SPI_H_
