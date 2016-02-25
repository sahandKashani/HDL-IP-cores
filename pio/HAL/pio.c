#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdbool.h>
#include <stdint.h>
#endif

#include "pio.h"
#include "pio_regs.h"

/*******************************************************************************
 *  Private API
 ******************************************************************************/

/*******************************************************************************
 *  Public API
 ******************************************************************************/
/*
 * pio_inst
 *
 * Constructs a device structure.
 */
pio_dev pio_inst(void *base, uint8_t data_width, uint32_t frequency, bool has_in, bool has_out, uint32_t reset_value) {
    pio_dev dev;

    dev.base = base;
    dev.data_width = data_width;
    dev.frequency = frequency;
    dev.has_in = has_in;
    dev.has_out = has_out;
    dev.reset_value = reset_value;

    return dev;
}

/*
 * pio_init
 *
 * Initializes the pio. If it is an output-only pio, then the device's value is
 * set to the reset value. If it is an input-only, or bidirectional pio, then
 * nothing is done.
 */
void pio_init(pio_dev *dev) {
    if (dev->has_out) {
        PIO_WR_DATA(dev->base, dev->reset_value);
    }
}

/*
 * pio_write_data
 *
 * Writes the 32-bit value provided as argument to the parallel port's data
 * register. Note that the intended result will only occur if the port's
 * direction is set to output)
 *
 * The result can only be as large as the max value supported by the parallel
 * port (depends on configuration width).
 */
void pio_write_data(pio_dev *dev, uint32_t data) {
    PIO_WR_DATA(dev->base, data);
}

/*
 * pio_read_data
 *
 * Reads a 32-bit value from the parallel port's data register. Note that the
 * intended result will only occur if the port's direction is set to input)
 *
 * The result can only be as large as the max value supported by the parallel
 * port (depends on configuration width).
 */
uint32_t pio_read_data(pio_dev *dev) {
    return PIO_RD_DATA(dev->base);
}
