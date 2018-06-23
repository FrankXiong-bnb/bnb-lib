#include "../standard/_definition.h"
#include "../standard/_ieee_754.h"
#include "../standard/_math.h"

_bnb_space_in

double __bnbcall hypot(double _a, double _b)
{
    double _result = 0;

    uint32 _ha, _hb;

    _get_double_bit_h(_ha, _a)
    _get_double_bit_h(_hb, _b)
    _ha &= 0x7fffffff;
    _hb &= 0x7fffffff;

    if(_hb > _ha)
    {
        double t = _a; _a = _b; _b = _a;
        _ha ^= _hb ^= _ha ^= _hb;
    }

    _set_double_bit_h(_a, _ha)
    _set_double_bit_h(_b, _hb)

    if(_ha - _hb > 0x03c00000)
        return (_a + _b);

    int32 _exp = 0;

    if(_ha > 0x5f300000)
    {
        if(_ha >= 0x7ff00000)
        {
            int32 _low;
            _result = _a + _b;

            _get_double_bit_l(_low, _a)
            if( !!!(_low | (_ha & 0x000fffff)) )
                _result = _a;

            _get_double_bit_l(_low, _b)
            if( !!!(_low | (_hb ^ 0x7ff00000)) )
                _result = _b;

            return _result;
        }

        _exp += 600;
        _ha -= 0x25800000;
        _hb -= 0x25800000;

        _set_double_bit_h(_a, _ha)
        _set_double_bit_h(_b, _hb)
    }

    if(_hb < 0x20b00000)
    {
        if(_hb <= 0x000fffff)
        {
            int32 _low;

            _get_double_bit_l(_low, _b)
            if( !!!(_low | _hb) )
                return _a;

            double _m = 0;
            _set_double_bit_h(_m, 0x7fd00000)

            _exp -= 1022;
            _a *= _m;
            _b *= _m;
        }
        else
        {
            _exp -= 600;
            _ha += 0x25800000;
            _hb += 0x25800000;

            _set_double_bit_h(_a, _ha)
            _set_double_bit_h(_b, _hb)
        }
    }

    _result = _a * sqrt(1 + (_b/_a)*(_b/_a));

    return ldexp(_result, _exp);
}

float __bnbcall hypot(float _a, float _b)
{
    float _result = 0;

    uint32 _ia, _ib;

    _get_digit_from_float(_ia, _a)
    _get_digit_from_float(_ib, _b)
    _ia &= 0x7fffffff;
    _ib &= 0x7fffffff;

    if(_ib > _ia)
    {
        double t = _a; _a = _b; _b = _a;
        _ia ^= _ib ^= _ia ^= _ib;
    }

    _set_float_from_digit(_a, _ia)
    _set_float_from_digit(_b, _ib)

    if(_ia - _ib > 0x0f000000)
        return (_a + _b);

    int32 _exp = 0;

    if(_ia > 0x58800000)
    {
        if(_ia >= 0x7f800000)
        {
            _result = _a + _b;

            if(_ia == 0x7f800000) _result = _a;
            if(_ib == 0x7f800000) _result = _b;

            return _result;
        }

        _exp += 60;
        _ia -= 0x5d800000;
        _ib -= 0x5d800000;

        _set_float_from_digit(_a, _ia)
        _set_float_from_digit(_b, _ib)
    }

    if(_ib < 0x26800000)
    {
        if(_ib > 0x007fffff)
        {
            _exp -= 60;
            _ia += 0x5d800000;
            _ib += 0x5d800000;

            _set_float_from_digit(_a, _ia)
            _set_float_from_digit(_b, _ib)
        }
        else
        {
            if( !!!_ib )
                return _a;

            float _m = 0;
            _set_float_from_digit(_m, 0x3f000000)

            _exp -= 126;
            _a *= _m;
            _b *= _m;
        }
    }

    _result = _a * sqrt(1 + (_b/_a)*(_b/_a));

    return ldexp(_result, _exp);
}

_bnb_space_out