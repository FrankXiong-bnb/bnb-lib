#ifndef ____bnb_Data_H_
#define ____bnb_Data_H_

#include "../standard/_definition.h"

_bnb_space_in

#define _min_int8           (-128i8)
#define _min_int16          (-32768i16)
#define _min_int32          (-2147483648i32)
#define _min_int64          (-9223372036854775808i64)

#define _min_char           (-128i8)
#define _min_short          (-32768i16)
#define _min_int            (-2147483648i32)
#define _min_long           (-2147483648L)
#define _min_longlong       (-9223372036854775808LL)

#define _max_byte           0xffui8
#define _max_byte2          0xffffui16
#define _max_byte4          0xffffffffui32
#define _max_byte8          0xffffffffffffffffui64
                                
#define _max_char           0x7fi8
#define _max_short          0x7fffi8
#define _max_int            0x7fffffffi32
#define _max_long           0x7fffffffL
#define _max_longlong       0x7fffffffffffffffi64

#define _max_uchar          0xffui8
#define _max_ushort         0xffffui16
#define _max_uint           0xffffffffui32
#define _max_ulong          0xffffffffUL
#define _max_ulonglong      0xffffffffffffffffui64

#define _max_int8           0x7fi8
#define _max_int16          0x7fffi16
#define _max_int32          0x7fffffffi32
#define _max_int64          0x7fffffffffffffffi64

#define _max_uint8          0xffui8
#define _max_uint16         0xffffui16
#define _max_uint32         0xffffffffui32
#define _max_uint64         0xffffffffffffffffui64


#define _max_string         _max_int32
#define _max_buffer         _max_byte2
#define _max_path           0x104ui32
#define _max_text           0x00800000ui32
#define _max_file           0x40000000ui32

#define _size_file_name     0x40        // 文件名大小
#define _size_string        0x80        // 字符串大小
#define _size_path          0xff        // 路径名大小
#define _size_buffer        0xff        // 缓冲区大小
#define _size_word          0x20        // 单词长度
#define _size_std_time      0x0a        // 时间长度

const unsigned int _size_char(sizeof(char));
const unsigned int _size_short(sizeof(int));
const unsigned int _size_int(sizeof(int));
const unsigned int _size_float(sizeof(float));
const unsigned int _size_long(sizeof(long));
const unsigned int _size_double(sizeof(double));
const unsigned int _size_longlong(sizeof(long long));
const unsigned int _size_longdouble(sizeof(long double));
const unsigned int _size_ptr(sizeof(void*));

_bnb_space_out

#endif