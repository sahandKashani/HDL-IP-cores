#ifndef __UART_H__
#define __UART_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdbool.h>
#include <stdint.h>
#endif

/* uart device structure */
typedef struct uart_dev {
    void     *base;
    uint32_t baud_rate;
    uint8_t  data_bits;
    bool     fixed_baud;
    uint32_t frequency;
    char     parity;
    uint8_t  stop_bits;
    bool     cts_rts;
    bool     eop_reg;
} uart_dev;

/*******************************************************************************
 *  Public API
 ******************************************************************************/
uart_dev uart_inst(void *base, uint32_t baud_rate, uint8_t data_bits, bool fixed_baud, uint32_t frequency, char parity, uint8_t stop_bits, bool cts_rts, bool eop_reg);

void uart_init(uart_dev *dev);

void uart_write(uart_dev *dev, uint8_t data);
int uart_read(uart_dev *dev, uint8_t *data);

void uart_write_multiple(uart_dev *dev, uint8_t *data, unsigned int len);
int uart_read_multiple(uart_dev *dev, uint8_t *data, unsigned int len);

#endif /* __UART_H__ */
