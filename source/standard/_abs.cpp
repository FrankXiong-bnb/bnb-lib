#include "../standard/_definition.h"
#include "../standard/_ieee_754.h"

_bnb_space_in

#ifndef abs

double __bnbcall abs( const double& _x )
{
    ieee_shape_double sd;

    sd._value = _x;
    sd._digit &= 0x7fffffffffffffff;
    
    return sd._value;
}

float __bnbcall abs( const float& _x )
{
    ieee_shape_float sf;

    sf._value = _x;
    sf._digit &= 0x7fffffff;

    return sf._value;
}

#endif // #ifndef abs

_bnb_space_out