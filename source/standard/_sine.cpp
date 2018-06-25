#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ... + [(-1)^n]*[x^(2*n+1)]/[(2*n+1)!]
    double _sin(double _radian)
    {
        if (_radian < 0)
            _radian -= ((long long)(_radian * _1_2pi - 0.5)) * _2pi;
        else
            _radian -= ((long long)(_radian * _1_2pi + 0.5)) * _2pi;

        if (abs(_radian) < _double_eps_root)
            return _radian;

        double _square = _radian * _radian;

        return _radian + _radian * ((((((((((1.95729410633912612308e-20
            * _square - 8.22063524662432971695e-18)
            * _square + 2.81145725434552076319e-15)
            * _square - 7.6471637318198164759e-13)
            * _square + 1.60590438368216145994e-10)
            * _square - 2.5052108385441718775e-8)
            * _square + 2.75573192239858906525e-6)
            * _square - 0.1984126984126984127e-3)
            * _square + 0.83333333333333333333e-2)
            * _square - 0.16666666666666666667)
            * _square);
    }

    float _sin(float _radian)
    {
        if (_radian < 0)
            _radian -= (float)(((int)(_radian * _1_2pi - 0.5)) * _2pi);
        else
            _radian -= (float)(((int)(_radian * _1_2pi + 0.5)) * _2pi);

        if (abs(_radian) < _float_eps_root)
            return _radian;

        float _square = _radian * _radian;

        return (float)(_radian + _radian * ((((0.2601903036e-5
            * _square - 0.1980741872e-03)
            * _square + 0.8333025139e-02)
            * _square - 0.1666665668)
            * _square));
    }

    double sin(double _radian)
    {
        switch (_check_numeral_type(_radian))
        {
        case _nt_nan:
            return _radian;
        case _nt_inf:
            return _double_not_number._value;
        default:
            return _sin(_radian);
        }
    }

    float sin(float _radian)
    {
        switch (_check_numeral_type(_radian))
        {
        case _nt_nan:
            return _radian;
        case _nt_inf:
            return _float_not_number._value;
        default:
            return _sin(_radian);
        }
    }

    double cos(double _radian)
    {
        switch (_check_numeral_type(_radian))
        {
        case _nt_nan:
            return _radian;
        case _nt_inf:
            return _double_not_number._value;
        default:
            return _sin(_pi_2 - _radian);
        }
    }

    float cos(float _radian)
    {
        switch (_check_numeral_type(_radian))
        {
        case _nt_nan:
            return _radian;
        case _nt_inf:
            return _float_not_number._value;
        default:
            return _sin((float)_pi_2 - _radian);
        }
    }

}
