#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    // arcsin(x) = x + x^3/(2*3) + (x^5)*(1*3)/(2*4*5) + (x^7)*(1*3*5)/(2*4*6*7) + ... + [x^(2*n+1)]*[(2*n-1)!!]/[(2*n)!!]/(2*n+1)
    double _arcsin(double _value)
    {
        double _radian = abs(_value);

        if (_radian < _double_eps_root)
            return _value;

        double _square = _radian * _radian;

        bool _half = _radian > 0.5;

        if (!!_half)
        {
            if (_radian > 1)
                return _double_not_number._value;

            _square = 0.5 - 0.5*_radian;
            _radian = -sqrt(_square);
            _radian += _radian;
        }

        _radian += _radian
            * (((((0.10152522233806463645e+2 - _square * 0.69674573447350646411)
                * _square - 0.39688862997404877339e+2)
                * _square + 0.57208227877891731407e+2)
                * _square - 0.27368494524164255994e+2)
                * _square)
            / (((((_square - 0.23823859153670238830e+2)
                * _square + 0.15095270841030604719e+3)
                * _square - 0.38186303361750149284e+3)
                * _square + 0.41714430248260412556e+3)
                * _square - 0.16421096714498560795e+3);

        if (!!_half)
            _radian += _pi_2;

        if (_value < 0)
            _radian = -_radian;

        return _radian;
    }

    float _arcsin(float _value)
    {
        float _radian = abs(_value);

        if (_radian < _float_eps_root)
            return _value;

        float _square = _radian * _radian;

        bool _half = _radian > 0.5f;

        if (!!_half)
        {
            if (_radian > 1)
                return _float_not_number._value;

            _square = 0.5f - 0.5f * _radian;
            _radian = -sqrt(_square);
            _radian += _radian;
        }

        _radian += (float)(_radian
            * ((0.933935835 - 0.504400557 * _square) * _square)
            / ((_square - 5.54846723) * _square + 5.60363004));

        if (!!_half)
            _radian += (float)_pi_2;

        if (_value < 0)
            _radian = -_radian;

        return _radian;
    }

    double arcsin(double _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
        case _nt_inf:
            return _double_not_number._value;
        default:
            return _arcsin(_value);

        }
    }

    float arcsin(float _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
        case _nt_inf:
            return _float_not_number._value;
        default:
            return _arcsin(_value);
        }
    }

    double arccos(double _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
        case _nt_inf:
            return _double_not_number._value;
        default:
            return (_pi_2 - _arcsin(_value));
        }
    }

    float arccos(float _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
        case _nt_inf:
            return _float_not_number._value;
        default:
            return (float)(_pi_2 - _arcsin(_value));
        }
    }

}
