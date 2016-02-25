#ifndef __UART_IO_H__
#define __UART_IO_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#define UART_CAST(type, ptr)       ((type) (ptr))

#define uart_write_word(dest, src) (*UART_CAST(volatile uint32_t *, (dest)) = (src))
#define uart_read_word(src)        (*UART_CAST(volatile uint32_t *, (src)))

#endif /* __UART_IO_H__ */
