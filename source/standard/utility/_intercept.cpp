#include "_math.h"

namespace bnb
{

    inline double ceil(double _digit)
    {
        double integer = 0;

        return ((modf(_digit, integer) > 0) ? (integer + 1) : integer);
    }

    inline float ceil(float _digit)
    {
        float integer = 0;

        return ((modf(_digit, integer) > 0) ? (integer + 1) : integer);
    }

    inline double floor(double _digit)
    {
        double integer = 0;

        return ((modf(_digit, integer) < 0) ? (integer - 1) : integer);
    }

    inline float floor(float _digit)
    {
        float integer = 0;

        return ((modf(_digit, integer) < 0) ? (integer - 1) : integer);
    }

}
