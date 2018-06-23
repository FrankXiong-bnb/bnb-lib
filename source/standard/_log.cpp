#include "../standard/_definition.h"
#include "../standard/_ieee_754.h"
#include "../standard/_constant.h"
#include "../standard/_math.h"

_bnb_space_in

// ln(x) = 2 * { (x-1)/(x+1) + [(x-1)/(x+1)]^3/3 +[(x-1)/(x+1)]^5/5 + ... + [(x-1)/(x+1)]^(2*n+1)/(2*n+1) }
double __bnbcall _ln( double _digit )
{
    double _series = (_digit-1) / (_digit+1);
    double _square = _series * _series;
    double _result = 1;
    unsigned int n = 1;

    for (double _factor = 1; _factor > _d_precision; ++n)
    {
        _factor *= _square;
        _result += (_factor / ((n<<1) + 1));
    }

    _result *= _series;
    return (_result + _result);
}

// ln(x) = 2 * { (x-1)/(x+1) + [(x-1)/(x+1)]^3/3 +[(x-1)/(x+1)]^5/5 + ... + [(x-1)/(x+1)]^(2*n+1)/(2*n+1) }
double __bnbcall ln( double _digit )
{
    if ( _ns_negative == _check_numeral_sign(_digit) )
        return _double_not_number._value;

    switch ( _check_numeral_type(_digit) )
    {
    case _nt_zero: case _nt_inf:
        return _double_infinite._value;
    case _nt_nan:
        return _double_not_number._value;
    }

    int _exp;

    _digit = frexp(_digit, _exp);

    double _series = _digit - 0.5;

    if (_digit > _sqrt2_2)
    {
        _series = (_series - 0.5) / (_digit * 0.5 + 0.5);
    }
    else
    {
        --_exp;
        _series /= (_series * 0.5 + 0.5);
    }

    double _factor = _series * _series;
    _series += _series
            * (((0.16383943563021534222e+02 - 0.78956112887481257267 * _factor)
                * _factor - 0.64124943423745581147e+02) * _factor)
            / (((_factor - 0.35667977739034646171e+02)
                * _factor + 0.31203222091924532844e+03)
                * _factor - 0.76949932108494879777e+03);

    _series += (_exp * 0.69314718055994530941);

    return (_series);
}

float __bnbcall ln( float _digit )
{
    if ( _ns_negative == _check_numeral_sign(_digit) )
        return _float_not_number._value;

    switch ( _check_numeral_type(_digit) )
    {
    case _nt_zero: case _nt_inf:
        return _float_infinite._value;
    case _nt_nan:
        return _float_not_number._value;
    }

    int _exp;

    _digit = frexp(_digit, _exp);

    float _series = _digit - 0.5f;

    if (_digit > _sqrt2_2)
    {
        _series = (_series - 0.5f) / (_digit * 0.5f + 0.5f);
    }
    else
    {
        --_exp;
        _series /= (_series * 0.5f + 0.5f);
    }

    float _factor = _series * _series;

    _series -= _series * _factor * 0.5527074855f / ((_factor + 1) * _factor - 6.632718214f);

    _series += (_exp * 0.6931471825f);

    return (_series);
}

double __bnbcall lg( double _digit )
{
    return (ln(_digit) * _1_ln10);
}

float __bnbcall lg( float _digit )
{
    return (float)(ln(_digit) * _1_ln10);
}

double __bnbcall lb( double _digit )
{
    return (ln(_digit) * _1_ln2);
}

float __bnbcall lb( float _digit )
{
    return (float)(ln(_digit) * _1_ln2);
}

double __bnbcall log( double _base, double _digit )
{
    return (ln(_digit) / ln(_base));
}

float __bnbcall log( float _base, float _digit )
{
    return (ln(_digit) / ln(_base));
}

_bnb_space_out