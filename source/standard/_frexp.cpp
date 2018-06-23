#include "../standard/_definition.h"
#include "../standard/_constant.h"
#include "../standard/_ieee_754.h"

_bnb_space_in

double __bnbcall frexp( double _digit, int& _index )
{
    if ( _nt_valid == _check_numeral_type(_digit) )
    {
        uint32 _h;

        _get_double_bit_h(_h, _digit)

        _index = ((_h & 0x7ff00000) >> 20) - 1022;

        _h &= 0x800fffff;
        _h |= 0x3fe00000;

        _set_double_bit_h(_digit, _h)
    }

    return (_digit);
}

float __bnbcall frexp( float _digit, int& _index )
{
    if ( _nt_valid == _check_numeral_type(_digit) )
    {
        uint16 _h;

        _get_float_bit_h(_h, _digit)

        _index = ((_h & 0x7f80) >> 7) - 126;

        _h &= 0x807f;
        _h |= 0x3f00;

        _set_float_bit_h(_digit, _h)
    }

    return (_digit);
}

_bnb_space_out