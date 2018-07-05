#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    // e^x = 1 + x + x^2/2! + x^3/3! + x^4/4! + ... + x^n/n!
    double _exp(double _index)
    {
        double _result = 1;
        unsigned int n = 1;

        for (double _series = 1; _series > _d_precision; ++n)
        {
            _series *= _index / n;
            _result += _series;
        }

        return _result;
    }

    // e^x = 2^(x*log2^e) = r * 2^n
    double exp(double _index)
    {
        switch (_check_numeral_type(_index))
        {
        case _nt_zero:
            return (1);
        case _nt_nan:
            return _index;
        case _nt_inf:
        {
            if (_ns_positive == _check_numeral_type(_index))
                return _double_infinite._value;
            else
                return 0;
        }
        default:
            break;
        }

        if (_digit_max_exp < _index || _index < _digit_min_exp)
            return _index;

        if (abs(_index) < _double_eps_root)
            return 1;

        int n = 0;
        if (_index < 0)
            n = (int)(_index * _1_ln2 - 0.5);
        else
            n = (int)(_index * _1_ln2 + 0.5);

        double _series = _index - n * _ln2;
        double _square = _series * _series;
        double _factor = _series * ((0.31555192765684646356e-4
            * _square + 0.75753180159422776666e-2)
            * _square + 0.25);
        double _digit = _factor / (((0.75104028399870046114e-6
            * _square + 0.63121894374398504557e-3)
            * _square + 0.56817302698551221787e-1)
            * _square + 0.5) - 0.5;

        return ldexp(_digit, ++n);
    }

    float exp(float _index)
    {
        switch (_check_numeral_type(_index))
        {
        case _nt_zero:
            return (1);
        case _nt_nan:
            return _index;
        case _nt_inf:
        {
            if (_ns_positive == _check_numeral_type(_index))
                return _float_infinite._value;
            else
                return 0;
        }
        default:
            break;
        }

        if (_digit_max_exp < _index || _index < _digit_min_exp)
            return _index;

        if (abs(_index) < _float_eps_root)
            return 1;

        int n = 0;
        if (_index < 0)
            n = (int)(_index * _1_ln2 - 0.5);
        else
            n = (int)(_index * _1_ln2 + 0.5);

        float _series = (float)(_index - n * _ln2);
        float _square = _series * _series;
        float _factor = _series * (0.00416028863f * _square + 0.24999999995f);
        float _digit = _factor / (0.04998717878f * _square + 0.5f) - 0.5f;

        return ldexp(_digit, ++n);
    }

}
