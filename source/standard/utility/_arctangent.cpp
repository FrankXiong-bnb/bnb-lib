#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    // arctan(x) = x - x^3/3 + x^5/5 - x^7/7 + ... ...[(-1)^n] * [x^(2n+1)] / [2n+1]
    double _arctan(double _value)
    {
        bool _inverse = (_value > 1.0);

        if (!!_inverse)
            _value = 1.0 / _value;

        double _offs = 0;

        if (_value > (2 - _sqrt3))
        {
            _value = ((_value * _sqrt3) - 1) / (_value + _sqrt3);
            _offs = _pi_6;
        }

        if (!!!(abs(_value) < _double_eps_root))
        {
            double _square = _value * _value;

            _value += (_value * (((-0.83758299368150059274
                * _square - 0.84946240351320683534e+1)
                * _square - 0.20505855195861651981e+2)
                * _square - 0.13688768894191926929e+2)
                * _square
                / ((((_square + 0.15024001160028576121e+2)
                    * _square + 0.59578436142597344465e+2)
                    * _square + 0.86157349597130242515e+2)
                    * _square + 0.41066306682575781263e+2));
        }

        _value += _offs;

        if (!!_inverse)
            _value = _pi_2 - _value;

        return (_value);
    }

    float _arctan(float _value)
    {
        bool _inverse = (_value > 1.0);

        if (!!_inverse)
            _value = 1.0f / _value;

        float _offs = 0;

        if (_value > (2 - _sqrt3))
        {
            _value = float(((_value * _sqrt3) - 1) / (_value + _sqrt3));
            _offs = (float)_pi_6;
        }

        if (!!!(abs(_value) < _float_eps_root))
        {
            float _square = _value * _value;

            _value += (_value * ((-0.05090958253f * _square - 0.4708325141f) * _square)
                / (_square + 1.41250074f));
        }

        _value += _offs;

        if (!!_inverse)
            _value = (float)_pi_2 - _value;

        return (_value);
    }

    double arctan(double _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
            return _double_not_number._value;
        case _nt_inf:
            return setsign(_pi_2, _value);
        default:
            break;
        }

        double _radian = _arctan(abs(_value));

        if (_value < 0)
            return (-_radian);

        return (_radian);
    }

    float arctan(float _value)
    {
        switch (_check_numeral_type(_value))
        {
        case _nt_nan:
            return _float_not_number._value;
        case _nt_inf:
            return setsign((float)_pi_2, _value);
        default:
            break;
        }

        float _radian = _arctan(abs(_value));

        if (_value < 0)
            return (-_radian);

        return (_radian);
    }

    double arctan(double _oppside, double _adjside)
    {
        double _radian = 0;

        if (_nt_zero == _check_numeral_type(_adjside))
        {
            if (_nt_zero == _check_numeral_type(_oppside))
                return _double_not_number._value;
            else
                _radian = _pi_2;
        }
        else
        {
            int _oppexp = 0, _adjexp = 0;

            frexp(_oppside, _oppexp);
            frexp(_adjside, _adjexp);

            int _expinv = _oppexp - _adjexp;

            if (_expinv > _double_exp_max)
                _radian = _pi_2;
            else if (_expinv < _double_exp_min)
                _radian = 0;
            else
                _radian = _arctan(abs(_oppside / _adjside));
        }

        if (_adjside < 0)
            _radian = _pi - _radian;

        if (_oppside < 0)
            _radian = -_radian;

        return (_radian);
    }

    float arctan(float _oppside, float _adjside)
    {
        float _radian = 0;

        if (_nt_zero == _check_numeral_type(_adjside))
        {
            if (_nt_zero == _check_numeral_type(_oppside))
                return _float_not_number._value;
            else
                _radian = (float)_pi_2;
        }
        else
        {
            int _oppexp = 0, _adjexp = 0;

            frexp(_oppside, _oppexp);
            frexp(_adjside, _adjexp);

            int _expinv = _oppexp - _adjexp;

            if (_expinv > _float_exp_max)
                _radian = (float)_pi_2;
            else if (_expinv < _float_exp_min)
                _radian = 0;
            else
                _radian = _arctan(abs(_oppside / _adjside));
        }

        if (_adjside < 0)
            _radian = (float)_pi - _radian;

        if (_oppside < 0)
            _radian = -_radian;

        return (_radian);
    }

}
