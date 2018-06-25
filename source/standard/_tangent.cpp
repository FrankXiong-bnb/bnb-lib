#include "_ieee_754.h"
#include "_math.h"

namespace bnb
{

    // tan(x) = E{ [x^(2n-1)] * [B(2n)] * [(2^2n) - 1] * (2^2n) * [(-1)^(n-1)] / [(2n)!] }
    // tan(x) = [sin(x) / sqrt(1 - sin(x)^2)]
    double tan(double _radian)
    {
        switch (_check_numeral_type(_radian))
        {
        case _nt_nan:
            return _radian;
        case _nt_inf:
            return _double_not_number._value;
        }

        if (_radian < 0)
            _radian -= ((long long)(_radian * _1_2pi - 0.5)) * _2pi;
        else
            _radian -= ((long long)(_radian * _1_2pi + 0.5)) * _2pi;

        if (abs(_radian) < _double_eps_root)
            return _radian;

        double _square = _radian * _radian;

        return (_radian * ((0.34248878235890589960e-2 - 0.17861707342254426711e-4 * _square)
            * _square - 0.13338350006421960681)
            * _square + _radian)
            / ((((0.49819433993786512270e-6
                * _square - 0.31181531907010027307e-3)
                * _square + 0.25663832289440112864e-1)
                * _square - 0.46671683339755294240)
                * _square + 1.0);
    }

    float tan(float _radian)
    {
        return (float)tan((double)_radian);
    }

}
