#include "_ieee_754.h"

namespace bnb
{

    double ldexp(double _digit, int n)
    {
        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned long long _exp, _i;

            _get_digit_from_double(_i, _digit)

            _exp = (_i & 0x7ff0000000000000) >> _double_man_len;
            _exp += n;

            if (_exp > _double_exp_max + _double_exp_off)
            {
                _digit = _double_infinite._value;
            }
            else if (_exp < _double_exp_min + _double_exp_off)
            {
                _digit = -_double_infinite._value;
            }
            else
            {
                _i &= 0x800fffffffffffff;
                _i |= _exp << _double_man_len;

                _set_double_from_digit(_digit, _i)
            }
        }

        return _digit;
    }

    float ldexp(float _digit, int n)
    {
        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned int _exp, _i;

            _get_digit_from_float(_i, _digit)

            _exp = (_i & 0x7f800000) >> _float_man_len;
            _exp += n;

            if (_exp > _float_exp_max + _float_exp_off)
            {
                _digit = _float_infinite._value;
            }
            else if (_exp < _float_exp_min + _float_exp_off)
            {
                _digit = -_float_infinite._value;
            }
            else
            {
                _i &= 0x807fffff;
                _i |= _exp << _float_man_len;

                _set_float_from_digit(_digit, _i)
            }
        }

        return _digit;
    }

}
