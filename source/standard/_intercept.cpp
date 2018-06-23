#include "../standard/_definition.h"
#include "../standard/_math.h"

_bnb_space_in

double __bnbcall ceil( double _digit )
{
    double integer = 0;

    return ( (modf(_digit, integer) > 0) ? (integer + 1) : integer );
}

float __bnbcall ceil( float _digit )
{
    float integer = 0;

    return ( (modf(_digit, integer) > 0) ? (integer + 1) : integer );
}

double __bnbcall floor( double _digit )
{
    double integer = 0;

    return ( (modf(_digit, integer) < 0) ? (integer - 1) : integer );
}

float __bnbcall floor( float _digit )
{
    float integer = 0;

    return ( (modf(_digit, integer) < 0) ? (integer - 1) : integer );
}

_bnb_space_out