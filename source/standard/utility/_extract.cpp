#include "_math.h"

namespace bnb
{

    // _digit^(1/n) = limitAm(m->infinite)  Am+1 = Am + [guess/(Am^(n-1)) - Am]/n
    double extract(double _digit, int n)
    {
        if (_digit > 0)
        {
            if (0 == n || 1.0 == _digit) return 1.0;

            unsigned int bit = abs(n), count = bit;
            const double _series = _digit / count;

            for (unsigned int i = 1; ; )
            {
                double _last = _digit;
                _digit = sqrt(_digit);

                i <<= 1, bit >>= 1;

                if (0 == bit)
                {
                    double l = 1.0 / i, r = l + l, m = 1.0 / count;

                    if (_digit > 1.0)
                    {
                        m = (m + l) * 0.5;
                        _digit = (_last - _digit) * (r - m) / (r - l) + _digit;
                    }
                    else
                    {
                        m = (m + r) * 0.5;
                        _digit = (_digit - _last) * (m - l) / (r - l) + _last;
                    }

                    break;
                }
            }

            double factor = _series / power(_digit, int(count - 1)) - _digit / count;

            for (_digit += factor; abs(factor) > 0.0000000000001; _digit += factor)
            {
                factor = _series / power(_digit, int(count - 1)) - _digit / count;
            }

            if (n < 0) return (1 / _digit);
        }

        return _digit;
    }

    float extract(float _digit, int n)
    {
        if (_digit > 0)
        {
            if (!!!n || 1.0 == _digit) return 1.0;

            unsigned int bit = abs(n), count = bit;
            const float _series = _digit / count;

            for (unsigned int i = 1; ; )
            {
                float _last = _digit;
                _digit = sqrt(_digit);

                i <<= 1, bit >>= 1;

                if (!!!bit)
                {
                    float l = 1.0f / i;
                    float r = l + l;
                    float m = 1.0f / count;

                    if (_digit > 1.0)
                    {
                        m = (m + l) * 0.5f;
                        _digit = (_last - _digit) * (r - m) / (r - l) + _digit;
                    }
                    else
                    {
                        m = (m + r) * 0.5f;
                        _digit = (_digit - _last) * (m - l) / (r - l) + _last;
                    }

                    break;
                }
            }

            float factor = _series / power(_digit, int(count - 1)) - _digit / count;

            for (_digit += factor; abs(factor) > _f_precision; _digit += factor)
            {
                factor = _series / power(_digit, int(count - 1)) - _digit / count;
            }

            if (n < 0) return (1 / _digit);
        }

        return _digit;
    }

}
