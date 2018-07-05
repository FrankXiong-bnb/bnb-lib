#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    double modf(double _digit, double& _part)
    {
        unsigned long long _i;

        _get_digit_from_double(_i, _digit)

        int _exp = ((_i & 0x7ff0000000000000) >> _double_man_len) - _double_exp_off;

        if (_exp < 0)
        {
            _part = setsign(0.0, _digit);
            return _digit;
        }

        if (_exp > _double_man_len)
        {
            _part = _digit;
            return setsign(0.0, _digit);
        }

        _i &= (~(0x000fffffffffffff >> _exp));
        _set_double_from_digit(_part, _i)

        return _digit - _part;
    }

    float modf(float _digit, float& _part)
    {
        unsigned int _i;

        _get_digit_from_float(_i, _digit)

        int _exp = ((_i & 0x7f800000) >> _float_man_len) - _float_exp_off;

        if (_exp < 0)
        {
            _part = setsign(0.0f, _digit);
            return _digit;
        }

        if (_exp > _float_man_len)
        {
            _part = _digit;
            return setsign(0.0f, _digit);
        }

        _i &= (~(0x007fffff >> _exp));
        _set_float_from_digit(_part, _i)

        return _digit - _part;
    }

    double fmod(double _x, double _y)
    {
        unsigned long long _ix, _iy;

        _get_digit_from_double(_ix, _x)
        _get_digit_from_double(_iy, _y)

        unsigned long long _xs = _ix & 0x8000000000000000;
        _ix ^= _xs;
        _iy &= 0x7fffffffffffffff;

        if (0 == _iy || (_iy > 0x7ff0000000000000) || (_ix >= 0x7ff0000000000000))
            return (_x * _y) / (_x * _y);

        if (_ix < _iy)
            return _x;

        if (_ix == _iy)
            return setsign(0.0, _x);

        long long _xe = -1022, _ye = -1022;

        if (_ix < 0x0010000000000000)
            for (long long i = (_ix << _double_exp_len); i > 0; i <<= 1)
                --_xe;
        else
            _xe = (_ix >> _double_man_len) - _double_exp_off;

        if (_iy < 0x0010000000000000)
            for (long long i = (_iy << _double_exp_len); i >= 0; i <<= 1)
                --_ye;
        else
            _ye = (_iy >> _double_man_len) - _double_exp_off;

        if (_xe < -1022)
            _ix <<= (-1022 - _xe);
        else
            _ix = 0x0010000000000000 | (0x000fffffffffffff & _ix);

        if (_ye < -1022)
            _iy <<= (-1022 - _ye);
        else
            _iy = 0x0010000000000000 | (0x000fffffffffffff & _iy);

        for (long long i = _xe - _ye; i > 0; --i)
        {
            if (_ix == _iy)
                return setsign(0.0, _x);

            if (_ix >= _iy)
                _ix -= _iy;

            _ix <<= 1;
        }

        if (_ix >= _iy)
            _ix -= _iy;

        if (!!!_ix)
            return setsign(0.0, _x);

        while (_ix < 0x0010000000000000)
        {
            _ix <<= 1;
            --_ye;
        }

        if (_ye < -1022)
            _ix >>= (-1022 - _ye);
        else
            _ix = (_ix - 0x0010000000000000) | ((_ye + _double_exp_off) << _double_man_len);

        _set_double_from_digit(_x, _ix | _xs)

        return _x;
    }

    float fmod(float _x, float _y)
    {
        unsigned int _ix, _iy;

        _get_digit_from_float(_ix, _x)
        _get_digit_from_float(_iy, _y)

        unsigned int _xs = _ix & 0x80000000;
        _ix ^= _xs;
        _iy &= 0x7fffffff;

        if (0 == _iy || (_iy > 0x7f800000) || (_ix >= 0x7f800000))
            return (_x * _y) / (_x * _y);

        if (_ix < _iy)
            return _x;

        if (_ix == _iy)
            return setsign(0.0f, _x);

        int _xe = -126, _ye = -126;

        if (_ix < 0x00800000)
            for (int i = _ix << _float_exp_len; i > 0; i <<= 1)
                --_xe;
        else
            _xe = (_ix >> _float_man_len) - _float_exp_off;

        if (_iy < 0x00800000)
            for (int i = (_iy << _float_exp_len); i >= 0; i <<= 1)
                --_ye;
        else
            _ye = (_iy >> _float_man_len) - _float_exp_off;

        if (_xe < -126)
            _ix <<= (-126 - _xe);
        else
            _ix = 0x00800000 | (0x007fffff & _ix);

        if (_ye < -126)
            _iy <<= (-126 - _ye);
        else
            _iy = 0x00800000 | (0x007fffff & _iy);

        for (int i = _xe - _ye; i > 0; --i)
        {
            if (_ix == _iy)
                return setsign(0.0f, _x);

            if (_ix >= _iy)
                _ix -= _iy;

            _ix <<= 1;
        }

        if (_ix >= _iy)
            _ix -= _iy;

        if (!!!_ix)
            return setsign(0.0f, _x);

        while (_ix < 0x00800000)
        {
            _ix <<= 1;
            --_ye;
        }

        if (_ye < -126)
            _ix >>= (-126 - _ye);
        else
            _ix = (_ix - 0x00800000) | ((_ye + _float_exp_off) << _float_man_len);

        _set_float_from_digit(_x, _ix | _xs)

        return _x;
    }

}
