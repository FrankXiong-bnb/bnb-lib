//=============================================================================
// math
// 													        2014-4 by Frank
//=============================================================================

#ifndef ____bnb_Math_H_
#define ____bnb_Math_H_

#include "_constant.h"

namespace bnb
{

#ifndef min
    template<typename _Ty> inline const _Ty& min(const _Ty& _a, const _Ty& _b) { return (_a < _b ? _a : _b); }
#endif

#ifndef max
    template<typename _Ty> inline const _Ty& max(const _Ty& _a, const _Ty& _b) { return (_a < _b ? _b : _a); }
#endif

#ifndef abs
    template<typename _Ty> inline _Ty abs(const _Ty& _x) { return ((_x < 0) ? (-_x) : _x); }
    float abs(const float& _x);
    double abs(const double& _x);
#endif

    template<typename _Ty> inline bool is_zero(const _Ty& _val) { return (_val == 0); }
    inline bool is_zero(const double& _val) { return (_d_precision > abs(_val)); }
    inline bool is_zero(const float& _val) { return (_f_precision > abs(_val)); }

    float setsign(const float& _digit, const float& _src);  // return value has the same sign as _src's
    float floor(float _digit);                              // return <= _digit
    float ceil(float _digit);                               // return >= _digit
    float modf(float _digit, float& _part);                 // _digit = (return) + (int)_part
    float fmod(float _x, float _y);                         // return _x % _y
    float exp(float _index);                                // return e^_index
    float ldexp(float _digit, int n);                       // return _digit*2^n(_digit<<n)
    float frexp(float _digit, int& _index);                 // _digit = (return)*2^_index
    float hypot(float _a, float _b);                        // return sqrt(_a^2 + _b^2)
    float extract(float _digit, int n);                     // return _digit^(1/n)
    float ln(float _digit);                                 // return log e^_digit
    inline float lg(float _digit) { return (float)(ln(_digit) * _1_ln10); }
    inline float lb(float _digit) { return (float)(ln(_digit) * _1_ln2); }
    inline float log(float _base, float _digit) { return (ln(_digit) / ln(_base)); }

    // exactly version
    double setsign(const double& _digit, const double& _src);
    double ceil(double _digit);
    double floor(double _digit);
    double fmod(double _x, double _y);
    double modf(double _digit, double& _part);
    double exp(double _index);
    double ldexp(double _digit, int n);
    double hypot(double _a, double _b);
    double frexp(double _digit, int& _index);
    double extract(double _digit, int n);
    double ln(double _digit);
    inline double lg(double _digit) { return (ln(_digit) * _1_ln10); }
    inline double lb(double _digit) { return (ln(_digit) * _1_ln2); }
    inline double log(double _base, double _digit) { return (ln(_digit) / ln(_base)); }
    
    // sqrt(_digit)
    double _sqrt(double _digit);
    float _sqrt(float _digit);
    double sqrt(double _digit);
    float sqrt(float _digit);

    // trigonometric function
    double _sin(double _radian);
    float _sin(float _radian);
    double sin(double _radian);
    double cos(double _radian);
    double tan(double _radian);
    float sin(float _radian);
    float cos(float _radian);
    float tan(float _radian);

    // anti-trigonometric function
    double _arcsin(double _radian);
    float _arcsin(float _radian);
    double arcsin(double _value);
    double arccos(double _value);
    double arctan(double _value);
    double arctan(double _oppside, double _adjside);
    float arcsin(float _value);
    float arccos(float _value);
    float arctan(float _value);
    float arctan(float _oppside, float _adjside);

    // return _x^n
    template<typename _Ty> inline _Ty _power(_Ty _x, int n)
    {
        unsigned int _count = (unsigned int)abs(n);

        for (_Ty _product = _Ty(1); ; _x *= _x)
        {
            if (_count & 1)
                _product *= _x;

            if (!!!(_count >>= 1))
                return ((n < 0) ? (_Ty(1) / _product) : _product);
        }
    }
    double power(double _x, int n);
    float power(float _x, int n);
    double power(double _x, double n);
    float power(float _x, float n);

    // return _a and _b greatest common divisor 
    unsigned int gcd(unsigned int _a, unsigned int _b);
    // return _a and _b least common multiple
    inline unsigned int lcm(unsigned int _a, unsigned int _b)
    {
        if (0 < _a && 0 < _b)
            return (_a * _b / gcd(_a, _b));

        return 0;
    }

    unsigned int lcm(unsigned int _a, unsigned int _b);

    inline double angle_to_radian(double _angle) { return (_angle * _pi_180); }
    inline double radian_to_angle(double _radian) { return (_radian * _180_pi); }
    inline float angle_to_radian(float _angle) { return (float)angle_to_radian((double)_angle); }
    inline float radian_to_angle(float _radian) { return (float)radian_to_angle((double)_radian); }

    // return n!
    inline unsigned int factorial(unsigned int n)
    {
        unsigned int fac = 1; while (n > 1) fac *= n--; return fac;
    }
    inline unsigned long long factorial(unsigned long n)
    {
        unsigned long long fac = 1; while (n > 1) fac *= n--; return fac;
    }

}

#endif
