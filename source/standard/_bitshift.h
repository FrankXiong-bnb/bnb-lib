#ifndef ____bnb_Bit_Shift_H_
#define ____bnb_Bit_Shift_H_

namespace bnb
{

    unsigned int bit_h32(unsigned long long u64) { return (u64 >> 32) & 0xffffffffui64; }
    unsigned int bit_l32(unsigned long long u64) { return (u64 & 0xffffffffui64); }
    unsigned short bit_h16(unsigned int u32) { return (u32 >> 16) & 0xffff; }
    unsigned short bit_l16(unsigned int u32) { return (u32 & 0xffff); }
    unsigned char bit_h8(unsigned short u16) { return (u16 >> 8) & 0xff; }
    unsigned char bit_l8(unsigned short u16) { return (u16 & 0xff); }
    unsigned long long make_bit64(unsigned int a, unsigned int b) { return (((unsigned long long)a & 0xffffffffui64) << 32) | (b & 0xffffffffui64); }
    unsigned int make_bit32(unsigned short a, unsigned short b) { return (((unsigned int)a & 0xffff) << 16) | (b & 0xffff); }
    unsigned short make_bit16(unsigned char a, unsigned char b) { return (((unsigned short)a & 0xff) << 8) | (b & 0xff); }

}

#endif
