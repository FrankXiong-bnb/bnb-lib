#include "_constant.h"
#include "_ieee_754.h"

namespace bnb
{

    double frexp(double _digit, int& _index)
    {
        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned int _h;

            _get_double_bit_h(_h, _digit)

            _index = ((_h & 0x7ff00000) >> 20) - 1022;

            _h &= 0x800fffff;
            _h |= 0x3fe00000;

            _set_double_bit_h(_digit, _h)
        }

        return (_digit);
    }

    float frexp(float _digit, int& _index)
    {
        if (_nt_valid == _check_numeral_type(_digit))
        {
            unsigned short _h;

            _get_float_bit_h(_h, _digit)

            _index = ((_h & 0x7f80) >> 7) - 126;

            _h &= 0x807f;
            _h |= 0x3f00;

            _set_float_bit_h(_digit, _h)
        }

        return (_digit);
    }

}
