#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    double _sqrt(double _digit)
    {
        if (_ns_negative == _check_numeral_sign(_digit))
            return _double_not_number._value;

        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned long long _guess;
            double _half = _digit * 0.5;

            _get_digit_from_double(_guess, _digit)
            _guess = 0x1ff7a00019870730ll + (_guess >> 1);
            _set_double_from_digit(_digit, _guess)

            _digit = _digit * 0.5 + _half / _digit;
            _digit = _digit * 0.5 + _half / _digit;
            _digit = _digit * 0.5 + _half / _digit;
        }

        return (_digit);
    }

    float _sqrt(float _digit)
    {
        if (_ns_negative == _check_numeral_sign(_digit))
            return _float_not_number._value;

        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned int _guess;
            float _half = _digit * 0.5f;

            _get_digit_from_float(_guess, _digit)
            _guess = 0x1fbb67adl + (_guess >> 1);
            _set_float_from_digit(_digit, _guess)

            _digit = _digit * 0.5f + _half / _digit;
            _digit = _digit * 0.5f + _half / _digit;
            _digit = _digit * 0.5f + _half / _digit;
        }

        return (_digit);
    }

    double sqrt(double _digit)
    {
        if (_ns_negative == _check_numeral_sign(_digit))
            return _double_not_number._value;

        if (_nt_valid == _check_numeral_type(_digit))
        {
            int _exp;

            double _guess = frexp(_digit, _exp);

            _digit = 0.41731 + 0.59016 * _guess;
            _guess *= 0.5;

            _digit = _digit * 0.5 + _guess / _digit;
            _digit = _digit * 0.5 + _guess / _digit;
            _digit = _digit * 0.5 + _guess / _digit;

            if (_exp & 1)
            {
                _digit *= 0.707106781186547524401;
                _exp++;
            }

            _digit = ldexp(_digit, _exp >> 1);
        }

        return (_digit);
    }

    float sqrt(float _digit)
    {
        if (_ns_negative == _check_numeral_sign(_digit))
            return _float_not_number._value;

        if (_nt_valid == _check_numeral_type(_digit))
        {
            int _exp;

            float _guess = frexp(_digit, _exp);

            _digit = 0.41731f + 0.59016f * _guess;
            _guess *= 0.5f;

            _digit = _digit * 0.5f + _guess / _digit;
            _digit = _digit * 0.5f + _guess / _digit;

            if (_exp & 1)
            {
                _digit *= 0.707106781f;
                _exp++;
            }

            _digit = ldexp(_digit, _exp >> 1);
        }

        return (_digit);
    }

}
