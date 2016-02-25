/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
******************************************************************************/

#ifndef __PIO_REGS_H__
#define __PIO_REGS_H__

#if defined(__KERNEL__) || defined(MODULE)
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#include "pio_io.h"

/* All registers are 32 bits wide */

#define PIO_DATA_OFST                 (0 * 4) /* RW */
#define PIO_DIRECTION_OFST            (1 * 4) /* RW */
#define PIO_IRQ_MASK_OFST             (2 * 4) /* RW */
#define PIO_EDGE_CAP_OFST             (3 * 4) /* RW */
#define PIO_SET_BITS_OFST             (4 * 4) /* WO */
#define PIO_CLEAR_BITS_OFST           (5 * 4) /* WO */

#define PIO_DATA_ADDR(base)           ((void *) ((uint8_t *) (base) + PIO_DATA_OFST))
#define PIO_DIRECTION_ADDR(base)      ((void *) ((uint8_t *) (base) + PIO_DIRECTION_OFST))
#define PIO_IRQ_ADDR(base)            ((void *) ((uint8_t *) (base) + PIO_IRQ_MASK_OFST))
#define PIO_EDGE_ADDR(base)           ((void *) ((uint8_t *) (base) + PIO_EDGE_CAP_OFST))
#define PIO_SET_ADDR(base)            ((void *) ((uint8_t *) (base) + PIO_SET_BITS_OFST))
#define PIO_CLEAR_ADDR(base)          ((void *) ((uint8_t *) (base) + PIO_CLEAR_BITS_OFST))

/* Defintions for direction-register operation with bi-directional PIOs */
#define PIO_DIRECTION_INPUT           (0)
#define PIO_DIRECTION_OUTPUT          (1)

#define PIO_WR_DATA(base, data)       pio_write_word(PIO_DATA_ADDR((base)), (data))
#define PIO_WR_DIRECTION(base, data)  pio_write_word(PIO_DIRECTION_ADDR((base)), (data))
#define PIO_WR_IRQ_MASK(base, data)   pio_write_word(PIO_IRQ_ADDR((base)), (data))
#define PIO_WR_EDGE_CAP(base, data)   pio_write_word(PIO_EDGE_ADDR((base)), (data))
#define PIO_WR_SET_BITS(base, data)   pio_write_word(PIO_SET_ADDR((base)), (data))
#define PIO_WR_CLEAR_BITS(base, data) pio_write_word(PIO_CLEAR_ADDR((base)), (data))
#define PIO_RD_DATA(base)             pio_read_word(PIO_DATA_ADDR((base)))
#define PIO_RD_DIRECTION(base)        pio_read_word(PIO_DIRECTION_ADDR((base)))
#define PIO_RD_IRQ_MASK(base)         pio_read_word(PIO_IRQ_ADDR((base)))
#define PIO_RD_EDGE_CAP(base)         pio_read_word(PIO_EDGE_ADDR((base)))

#endif /* __PIO_REGS_H__ */
