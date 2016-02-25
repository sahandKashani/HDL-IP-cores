#ifndef __UART_REGS_H__
#define __UART_REGS_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#include "uart_io.h"

/* All registers are 32 bits wide */

#define UART_RXDATA_REG_OFST        (0 * 4) /* RO */
#define UART_TXDATA_REG_OFST        (1 * 4) /* WO */
#define UART_STATUS_REG_OFST        (2 * 4) /* RW */
#define UART_CONTROL_REG_OFST       (3 * 4) /* RW */
#define UART_DIVISOR_REG_OFST       (4 * 4) /* RW */
#define UART_EOP_REG_OFST           (5 * 4) /* RW */

#define UART_RXDATA_ADDR(base)      ((void *) ((uint8_t *) (base) + UART_RXDATA_REG_OFST))
#define UART_TXDATA_ADDR(base)      ((void *) ((uint8_t *) (base) + UART_TXDATA_REG_OFST))
#define UART_STATUS_ADDR(base)      ((void *) ((uint8_t *) (base) + UART_STATUS_REG_OFST))
#define UART_CONTROL_ADDR(base)     ((void *) ((uint8_t *) (base) + UART_CONTROL_REG_OFST))
#define UART_DIVISOR_ADDR(base)     ((void *) ((uint8_t *) (base) + UART_DIVISOR_REG_OFST))
#define UART_EOP_ADDR(base)         ((void *) ((uint8_t *) (base) + UART_EOP_REG_OFST))

#define UART_STATUS_PE_MSK          (0x1)
#define UART_STATUS_PE_OFST         (0)
#define UART_STATUS_FE_MSK          (0x2)
#define UART_STATUS_FE_OFST         (1)
#define UART_STATUS_BRK_MSK         (0x4)
#define UART_STATUS_BRK_OFST        (2)
#define UART_STATUS_ROE_MSK         (0x8)
#define UART_STATUS_ROE_OFST        (3)
#define UART_STATUS_TOE_MSK         (0x10)
#define UART_STATUS_TOE_OFST        (4)
#define UART_STATUS_TMT_MSK         (0x20)
#define UART_STATUS_TMT_OFST        (5)
#define UART_STATUS_TRDY_MSK        (0x40)
#define UART_STATUS_TRDY_OFST       (6)
#define UART_STATUS_RRDY_MSK        (0x80)
#define UART_STATUS_RRDY_OFST       (7)
#define UART_STATUS_E_MSK           (0x100)
#define UART_STATUS_E_OFST          (8)
#define UART_STATUS_DCTS_MSK        (0x400)
#define UART_STATUS_DCTS_OFST       (10)
#define UART_STATUS_CTS_MSK         (0x800)
#define UART_STATUS_CTS_OFST        (11)
#define UART_STATUS_EOP_MSK         (0x1000)
#define UART_STATUS_EOP_OFST        (12)

#define UART_CONTROL_PE_MSK         (0x1)
#define UART_CONTROL_PE_OFST        (0)
#define UART_CONTROL_FE_MSK         (0x2)
#define UART_CONTROL_FE_OFST        (1)
#define UART_CONTROL_BRK_MSK        (0x4)
#define UART_CONTROL_BRK_OFST       (2)
#define UART_CONTROL_ROE_MSK        (0x8)
#define UART_CONTROL_ROE_OFST       (3)
#define UART_CONTROL_TOE_MSK        (0x10)
#define UART_CONTROL_TOE_OFST       (4)
#define UART_CONTROL_TMT_MSK        (0x20)
#define UART_CONTROL_TMT_OFST       (5)
#define UART_CONTROL_TRDY_MSK       (0x40)
#define UART_CONTROL_TRDY_OFST      (6)
#define UART_CONTROL_RRDY_MSK       (0x80)
#define UART_CONTROL_RRDY_OFST      (7)
#define UART_CONTROL_E_MSK          (0x100)
#define UART_CONTROL_E_OFST         (8)
#define UART_CONTROL_DCTS_MSK       (0x400)
#define UART_CONTROL_DCTS_OFST      (10)
#define UART_CONTROL_RTS_MSK        (0x800)
#define UART_CONTROL_RTS_OFST       (11)
#define UART_CONTROL_EOP_MSK        (0x1000)
#define UART_CONTROL_EOP_OFST       (12)

#define UART_EOP_MSK                (0xff)
#define UART_EOP_OFST               (0)

#define UART_WR_TXDATA(base, data)  uart_write_word(UART_TXDATA_ADDR((base)), (data))
#define UART_WR_STATUS(base, data)  uart_write_word(UART_STATUS_ADDR((base)), (data))
#define UART_WR_CONTROL(base, data) uart_write_word(UART_CONTROL_ADDR((base)), (data))
#define UART_WR_DIVISOR(base, data) uart_write_word(UART_DIVISOR_ADDR((base)), (data))
#define UART_WR_EOP(base, data)     uart_write_word(UART_EOP_ADDR((base)), (data))
#define UART_RD_RXDATA(base)        uart_read_word(UART_RXDATA_ADDR((base)))
#define UART_RD_STATUS(base)        uart_read_word(UART_STATUS_ADDR((base)))
#define UART_RD_CONTROL(base)       uart_read_word(UART_CONTROL_ADDR((base)))
#define UART_RD_DIVISOR(base)       uart_read_word(UART_DIVISOR_ADDR((base)))
#define UART_RD_EOP(base)           uart_read_word(UART_EOP_ADDR((base)))

#endif /* __UART_REGS_H__ */
