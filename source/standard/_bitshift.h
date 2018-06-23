#ifndef ____bnb_Bit_Shift_H_
#define ____bnb_Bit_Shift_H_

#include "../standard/_tydef.h"

_bnb_space_in

#define bit_h32(u64)            ((byte_4)((((byte_8)(u64)) >> 32) & 0xffffffffui64))
#define bit_l32(u64)            ((byte_4)(((byte_8)(u64)) & 0xffffffffui64))

#define bit_h16(u32)            ((byte_2)((((byte_4)(u32)) >> 16) & 0xffff))
#define bit_l16(u32)            ((byte_2)(((byte_4)(u32)) & 0xffff))

#define bit_h8(u16)             ((byte_1)((((byte_2)(u16)) >> 8) & 0xff))
#define bit_l8(u16)             ((byte_1)(((byte_2)(u16)) & 0xff))

#define bit_make64(h32, l32)    ((byte_8)(((((byte_8)(h32)) & 0xffffffffui64) << 32) | (((byte_8)(l32)) & 0xffffffffui64)))
#define bit_make32(h16, l16)    ((byte_4)(((((byte_4)(h16)) & 0xffff) << 16) | (((byte_4)(l16)) & 0xffff)))
#define bit_make16(h8, l8)      ((byte_2)(((((byte_2)(h8)) & 0xff) << 8) | (((byte_2)(l8)) & 0xff)))

_bnb_space_out

#endif