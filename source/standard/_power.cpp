#include "../standard/_definition.h"
#include "../standard/_ieee_754.h"
#include "../standard/_math.h"

_bnb_space_in

double __bnbcall power( double _x, int n )
{
    return _power(_x, n);
}

float __bnbcall power( float _x, int n )
{
    return _power(_x, n);;
}

// x^n = (e^ln(x))^n = e^(n * ln(x))
double __bnbcall power( double _x, double n )
{
    if ( !!is_zero(_x) )
        return _x;

    double _integer;
    double _decimal = modf(n, _integer);

    _numeral_sign _sign = _check_numeral_sign(_x);
    bool _inv = is_zero(_decimal);

    if ( _ns_negative == _sign )
        if ( !!!_inv )
            return _double_not_number._value;

    double _exp = n * ln(abs(_x));

    if ( _exp <= _digit_min_exp )
        return (_zero);

    if ( _exp >= _digit_max_exp )
    {
        if ( _ns_negative == _sign )
            if ( (uint64)_integer % 2 )
                return -_double_infinite._value;

        return _double_infinite._value;
    }

    if ( _inv )
        return _power(_x, (int)_integer);
    else
        return exp(_exp);
}

float __bnbcall power( float _x, float n )
{
    if ( !!is_zero(_x) )
        return _x;

    float _integer;
    float _decimal = modf(n, _integer);

    _numeral_sign _sign = _check_numeral_sign(_x);
    bool _inv = is_zero(_decimal);

    if ( _ns_negative == _sign )
        if ( !!!_inv )
            return _float_not_number._value;

    float _exp = n * ln(abs(_x));

    if ( _exp <= _digit_min_exp )
        return (_zero);

    if ( _exp >= _digit_max_exp )
    {
        if ( _ns_negative == _sign )
            if ( (uint32)_integer % 2 )
                return -_float_infinite._value;

        return _float_infinite._value;
    }

    if ( _inv )
        return _power(_x, (int)_integer);
    else
        return exp(_exp);
}

_bnb_space_out