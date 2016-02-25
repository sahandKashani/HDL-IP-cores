#ifndef __PIO_H__
#define __PIO_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdbool.h>
#include <stdint.h>
#endif

/* pio device structure */
typedef struct pio_dev {
    void     *base;
    uint8_t  data_width;
    uint32_t frequency;
    bool     has_in;
    bool     has_out;
    uint32_t reset_value;
} pio_dev;

/*******************************************************************************
 *  Public API
 ******************************************************************************/
pio_dev pio_inst(void *base, uint8_t data_width, uint32_t frequency, bool has_in, bool has_out, uint32_t reset_value);

void pio_init(pio_dev *dev);

void pio_write_data(pio_dev *dev, uint32_t data);
uint32_t pio_read_data(pio_dev *dev);

#endif /* __PIO_H__ */
