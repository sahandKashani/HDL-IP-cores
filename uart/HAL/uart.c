#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdbool.h>
#include <stdint.h>
#endif

#include "uart.h"
#include "uart_regs.h"

/*******************************************************************************
 *  Private API
 ******************************************************************************/

/*******************************************************************************
 *  Public API
 ******************************************************************************/
/*
 * uart_inst
 *
 * Constructs a device structure.
 */
uart_dev uart_inst(void *base, uint32_t baud_rate, uint8_t data_bits, bool fixed_baud, uint32_t frequency, char parity, uint8_t stop_bits, bool cts_rts, bool eop_reg) {
    uart_dev dev;

    dev.base = base;
    dev.baud_rate = baud_rate;
    dev.data_bits = data_bits;
    dev.fixed_baud = fixed_baud;
    dev.frequency = frequency;
    dev.parity = parity;
    dev.stop_bits = stop_bits;
    dev.cts_rts = cts_rts;
    dev.eop_reg = eop_reg;

    return dev;
}

/*
 * uart_init
 *
 * Initializes the uart. This function clears any error bits set in the status
 * register.
 */
void uart_init(uart_dev *dev) {
    /* clear any error flags */
    UART_WR_STATUS(dev->base, 0);
}

/*
 * uart_write
 *
 * Sends a byte through the uart. This function blocks until the uart is
 * available before writing its value to the device.
 */
void uart_write(uart_dev *dev, uint8_t data) {
    /* wait until device is ready to send new data */
    while (!(UART_RD_STATUS(dev->base) & UART_STATUS_TRDY_MSK));

    UART_WR_TXDATA(dev->base, data);
}

/*
 * uart_read
 *
 * Receives a byte through the uart. This function blocks until the uart has
 * data available before reading its value from the device.
 *
 * The return value is the number of bytes successfully read (0 or 1).
 */
int uart_read(uart_dev *dev, uint8_t *data) {
    uint16_t status = 0;

    do {
        status = UART_RD_STATUS(dev->base);

        /* clear any error flags */
        UART_WR_STATUS(dev->base, 0);
    } while (!(status & UART_STATUS_RRDY_MSK));

    if (status & (UART_STATUS_PE_MSK | UART_STATUS_FE_MSK)) {
        return 0;
    }

    return 1;
}

/*
 * uart_write_multiple
 *
 * Sends len bytes through the uart. This function blocks until all the data is
 * sent.
 */
void uart_write_multiple(uart_dev *dev, uint8_t *data, unsigned int len) {
    unsigned int i = 0;

    for (i = 0; i < len; i++) {
        uart_write(dev, data[i]);
    }
}

/*
 * uart_read_multiple
 *
 * Receives len bytes through the uart. This function blocks until all the data
 * has been read, or until any errors are encountered.
 *
 * The return value is the number of bytes successfully read (0 <= ret <= len).
 */
int uart_read_multiple(uart_dev *dev, uint8_t *data, unsigned int len) {
    unsigned int i = 0;

    for (i = 0; i < len; i++) {
        if (!uart_read(dev, data + i)) {
            return i;
        }
    }

    return len;
}
