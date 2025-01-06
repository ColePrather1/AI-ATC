


#include "RF24.h"


void RF24::read_payload(void* buf, uint8_t data_len)
{
    uint8_t* current = reinterpret_cast<uint8_t*>(buf);

    uint8_t blank_len = 0;
    if (!dynamic_payloads_enabled) {
        data_len = rf24_min(data_len, payload_size);
        blank_len = static_cast<uint8_t>(payload_size - data_len);
    }
    else {
        data_len = rf24_min(data_len, static_cast<uint8_t>(32));
    }

    //printf("[Reading %u bytes %u blanks]",data_len,blank_len);

    IF_RF24_DEBUG(printf_P("[Reading %u bytes %u blanks]\n", data_len, blank_len););

#if defined(RF24_LINUX) || defined(RF24_RP2)
    beginTransaction();
    uint8_t* prx = spi_rxbuff;
    uint8_t* ptx = spi_txbuff;
    uint8_t size;
    size = static_cast<uint8_t>(data_len + blank_len + 1); // Add register value to transmit buffer

    *ptx++ = R_RX_PAYLOAD;
    while (--size) {
        *ptx++ = RF24_NOP;
    }

    size = static_cast<uint8_t>(data_len + blank_len + 1); // Size has been lost during while, re affect

    #if defined(RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, size);
    #else  // !defined(RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char*>(spi_txbuff), reinterpret_cast<char*>(spi_rxbuff), size);
    #endif // !defined(RF24_RP2)

    status = *prx++; // 1st byte is status

    if (data_len > 0) {
        // Decrement before to skip 1st status byte
        while (--data_len) {
            *current++ = *prx++;
        }

        *current = *prx;
    }
    endTransaction();
#else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
    #if defined(RF24_SPI_PTR)
    status = _spi->transfer(R_RX_PAYLOAD);
    while (data_len--) {
        *current++ = _spi->transfer(0xFF);
    }

    while (blank_len--) {
        _spi->transfer(0xFF);
    }

    #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(R_RX_PAYLOAD);
    while (data_len--) {
        *current++ = _SPI.transfer(0xFF);
    }

    while (blank_len--) {
        _SPI.transfer(0xff);
    }

    #endif // !defined(RF24_SPI_PTR)
    endTransaction();

#endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
}


