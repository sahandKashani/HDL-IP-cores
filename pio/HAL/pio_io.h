#ifndef __PIO_IO_H__
#define __PIO_IO_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#define PIO_CAST(type, ptr)       ((type) (ptr))

#define pio_write_word(dest, src) (*PIO_CAST(volatile uint32_t *, (dest)) = (src))
#define pio_read_word(src)        (*PIO_CAST(volatile uint32_t *, (src)))

#endif /* __PIO_IO_H__ */
