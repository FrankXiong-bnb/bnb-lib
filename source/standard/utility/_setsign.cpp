#include "_ieee_754.h"

namespace bnb
{

    double setsign(const double& _digit, const double& _src)
    {
        ieee_shape_double sd;
        sd._value = _src;

        unsigned long long _sign = sd._digit & 0x8000000000000000;

        sd._value = _digit;
        sd._digit &= 0x7fffffffffffffff;
        sd._digit |= _sign;

        return sd._value;
    }

    float setsign(const float& _digit, const float& _src)
    {
        ieee_shape_float sf;
        sf._value = _src;

        unsigned int _sign = sf._digit & 0x80000000;

        sf._value = _digit;
        sf._digit &= 0x7fffffff;
        sf._digit |= _sign;

        return sf._value;
    }

}
