#include "../standard/_definition.h"

_bnb_space_in
    
unsigned int __bnbcall gcd( unsigned int _a, unsigned int _b )
{
    if ( !!!(_a || _b) )
        return (0);

    if (_a > _b)
        _a ^= _b ^= _a ^= _b;

    while ( _a ) 
    {
        unsigned int _r = _b % _a;
        _b = _a;
        _a = _r;
    }

    return _b;
}

unsigned int __bnbcall lcm( unsigned int _a, unsigned int _b )
{
    if ( !!!(_a || _b) )
        return (0);

    return (_a * _b / gcd(_a, _b));
}

_bnb_space_out