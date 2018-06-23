//=============================================================================
// Explanation:
// 		IEEE 754
// 													Date: 2014-4 Author: Frank
//=============================================================================
#ifndef ____bnb_IEEEE_754_H_
#define ____bnb_IEEEE_754_H_

#include "../standard/_tydef.h"

_bnb_space_in

enum _endian_type {
    _big_endian,
    _little_endian
};

#ifndef _ieee_big_endian
#define _ieee_endian _little_endian
#else
#define _ieee_endian _big_endian
#endif  // #ifndef _ieee_big_endian

#if _ieee_endian == _little_endian

typedef union {
    double  _value;

    struct {
        uint32  _lb;
        uint32  _hb;
    } _word;
} ieee_bit_double;

typedef union {
    float  _value;

    struct {
        uint16  _lb;
        uint16  _hb;
    } _word;
} ieee_bit_float;

#else   // _ieee_endian == _big_endian

typedef union {
    double  _value;

    struct {
        uint32  _hb;
        uint32  _lb;
    } _word;
} ieee_bit_double;

typedef union {
    float  _value;

    struct {
        uint16  _hb;
        uint16  _lb;
    } _word;
} ieee_bit_float;

#endif  // #if _ieee_endian

#define _extract_double(_d, _h, _l) {   \
_bnb ieee_bit_double _ibd;              \
_ibd._value = (_d);                     \
(_h) = _ibd._word._hb;                  \
(_l) = _ibd._word._lb; }

#define _insert_double(_d, _h, _l) {    \
_bnb ieee_bit_double _ibd;              \
_ibd._word._hb = (_h);                  \
_ibd._word._lb = (_l);                  \
(_d) = _ibd._value; }

#define _set_double_bit_h(_d, _i) {     \
_bnb ieee_bit_double _ibd;              \
_ibd._value = (_d);                     \
_ibd._word._hb = (_i);                  \
(_d) = _ibd._value; }

#define _set_double_bit_l(_d, _i) {     \
_bnb ieee_bit_double _ibd;              \
_ibd._value = (_d);                     \
_ibd._word._lb = (_i);                  \
(_d) = _ibd._value; }

#define _get_double_bit_h(_i, _d) {     \
_bnb ieee_bit_double _ibd;              \
_ibd._value = (_d);                     \
(_i) = _ibd._word._hb; }

#define _get_double_bit_l(_i, _d) {     \
_bnb ieee_bit_double _ibd;              \
_ibd._value = (_d);                     \
(_i) = _ibd._word._lb; }

#define _extract_float(_f, _h, _l) {    \
_bnb ieee_bit_float _ibf;               \
_ibf._value = (_f);                     \
(_h) = _ibf._word._hb;                  \
(_l) = _ibf._word._lb; }

#define _insert_float(_f, _h, _l) {     \
_bnb ieee_bit_float _ibf;               \
_ibf._word._hb = (_h);                  \
_ibf._word._lb = (_l);                  \
(_f) = _ibf._value; }

#define _set_float_bit_h(_f, _i) {      \
_bnb ieee_bit_float _ibf;               \
_ibf._value = (_f);                     \
_ibf._word._hb = (_i);                  \
(_f) = _ibf._value; }

#define _set_float_bit_l(_f, _i) {      \
_bnb ieee_bit_float _ibf;               \
_ibf._value = (_f);                     \
_ibf._word._lb = (_i);                  \
(_f) = _ibf._value; }

#define _get_float_bit_h(_i, _f) {      \
_bnb ieee_bit_float _ibf;               \
_ibf._value = (_f);                     \
(_i) = _ibf._word._hb; }

#define _get_float_bit_l(_i, _f) {      \
_bnb ieee_bit_float _ibf;               \
_ibf._value = (_f);                     \
(_i) = _ibf._word._lb; }

typedef union {
    double  _value;
    uint64  _digit;
} ieee_shape_double;

#define _set_double_from_digit(_d, _i) {    \
_bnb ieee_shape_double _isd;                \
_isd._digit = (_i);                         \
(_d) = _isd._value; }

#define _get_digit_from_double(_i, _d) {    \
_bnb ieee_shape_double _isd;                \
_isd._value = (_d);                         \
(_i) = _isd._digit; }

typedef union {
    float   _value;
    uint32  _digit;
} ieee_shape_float;

#define _set_float_from_digit(_f, _i) {     \
_bnb ieee_shape_float _isf;                 \
_isf._digit = (_i);                         \
(_f) = _isf._value; }

#define _get_digit_from_float(_i, _f) {     \
_bnb ieee_shape_float _isf;                 \
_isf._value = (_f);                         \
(_i) = _isf._digit; }


/*
 *	float:
 *
 *     31 30           23 22                                    0
 *      | |             | |                                     |
 *      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ... 0 0 0 0 0 0 0 0 0 0
 *      |  \           /   \                                   /
 *    sign  \__ exp __/     \_____________ mantissa __________/
 *
 *  double:
 *
 *     63 62                 52 51                                          0
 *      | |                   | |                                           |
 *      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ... 0 0 0 0 0 0 0 0 0 0 0
 *      |  \                 /   \                                         /
 *    sign  \_____ exp _____/     \_______________ mantissa ______________/
 */

const int _sign_len(1);

const int _double_man_len(52);
const int _double_exp_len(11);
const int _double_exp_off(1023);
const int _double_exp_max(1024);
const int _double_exp_min(-1021);

const int _float_man_len(23);
const int _float_exp_len(8);
const int _float_exp_off(127);
const int _float_exp_max(128);
const int _float_exp_min(-125);

enum _numeral_type {
    _nt_zero,           // 0
    _nt_inf,            // infinite
    _nt_nan,            // not number
    _nt_valid           // valid number
};

enum _numeral_sign {
    _ns_positive,
    _ns_negative
};

union _ieee_shape_double {
    uint64  _digit;
    double  _value;
};

union _ieee_shape_float {
    uint32  _digit;
    float   _value;
};

const double _digit_max_exp(7.09782712893383973096e+2);
const double _digit_min_exp(-7.45133219101941108420e+2);
const double _double_eps_root(7.4505859692e-9);
const float  _float_eps_root(0.0017263349182589107f);

const _ieee_shape_double    _double_infinite     = { 0x7ff0000000000000 };
const _ieee_shape_double    _double_not_number   = { 0xfffa000000000000 };
const _ieee_shape_float     _float_infinite      = { 0x7f800000 };
const _ieee_shape_float     _float_not_number    = { 0xffd00000 };

inline _numeral_type __bnbcall _check_numeral_type( _in const double& _digit )
{
    uint64 _i, _exp;

    _get_digit_from_double(_i, _digit)

    _exp = (_i & 0x7ff0000000000000) >> _double_man_len;

    if ( !!!_exp )
        if ( !!!(_i & 0xfffffffffffff) )
            return (_nt_zero);

    if ( _exp == _double_exp_max + _double_exp_off )
    {
        if (_i & 0xfffffffffffff)
            return (_nt_nan);
        else
            return (_nt_inf);
    }

    return (_nt_valid);
}

inline _numeral_type __bnbcall _check_numeral_type( _in const float& _digit )
{
    uint32 _i, _exp;

    _get_digit_from_float(_i, _digit)

    _exp = (_i & 0x7f800000) >> _float_man_len;

    if ( !!!_exp )
        if ( !!!(_i & 0x7fffff) )
            return (_nt_zero);

    if ( _exp == _float_exp_max + _float_exp_off )
    {
        if (_i & 0x7fffff)
            return (_nt_nan);
        else
            return (_nt_inf);
    }

    return (_nt_valid);
}

inline _numeral_sign __bnbcall _check_numeral_sign( _in const double& _digit )
{
    uint32 _h;
    
    _get_double_bit_h(_h, _digit)

    if (_h & 0x80000000)      
        return (_ns_negative);   
    else
        return (_ns_positive);
}

inline _numeral_sign __bnbcall _check_numeral_sign( _in const float& _digit )
{
    uint16 _h;

    _get_float_bit_h(_h, _digit)

    if (_h & 0x8000)      
        return (_ns_negative);   
    else
        return (_ns_positive);
}

inline _endian_type __bnbcall _check_endian()
{
    const union {
        byte_2 _value;
        byte_1 _endian; }
    _test_endian = { _little_endian | _big_endian };

    return static_cast<_endian_type>(_test_endian._endian);
}

_bnb_space_out
    
#endif