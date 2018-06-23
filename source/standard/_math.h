//=============================================================================
// math
// 													        2014-4 by Frank
//=============================================================================

#ifndef ____bnb_Math_H_
#define ____bnb_Math_H_

_bnb_space_in

#ifndef _zero
#define _zero   0
#endif

const double _f_precision(0.000001);
const double _d_precision(0.0000000000000001);

#ifdef  _not_high_precision
#define _precision  _f_precision
#else
#define _precision  _d_precision
#endif  // #ifdef  _not_high_precision

#ifndef min
template<typename _Ty> inline const _Ty& min( _in const _Ty& _a, _in const _Ty& _b ) { return (_a < _b ? _a : _b); }
#endif

#ifndef max
template<typename _Ty> inline const _Ty& max( _in const _Ty& _a, _in const _Ty& _b ) { return (_a < _b ? _b : _a); }
#endif

#ifndef abs
template<typename _Ty> inline _Ty abs( _in const _Ty& _x ) { return ( (_x < 0) ? (-_x) : _x ); }
float __bnbcall abs( _in const float& _x );
double __bnbcall abs( _in const double& _x );
#endif

template<typename _Ty> inline bool is_zero( _in const _Ty& _val ) { return (_val == _zero); }
inline bool is_zero( _in const double& _val ) { return (_d_precision > abs(_val)); } 
inline bool is_zero( _in const float& _val )  { return (_f_precision > abs(_val)); }

float __bnbcall setsign( _in const float& _digit, _in const float& _src );  // return value has the same sign as _src's
float __bnbcall floor( _in float _digit );                                  // return <= _digit
float __bnbcall ceil( _in float _digit );                                   // return >= _digit
float __bnbcall modf( _in float _digit, _out float& _part );                // _digit = (return) + (int)_part
float __bnbcall fmod( _in float _x, _in float _y );                         // return _x % _y
float __bnbcall ldexp( _in float _digit, _in int n );                       // return _digit*2^n(_digit<<n)
float __bnbcall frexp( _in float _digit, _out int& _index );                // _digit = (return)*2^_index
float __bnbcall hypot( _in float _a, _in float _b );                        // return sqrt(_a^2 + _b^2)
float __bnbcall extract( _in float _digit, _in int n);                      // return _digit^(1/n)
float __bnbcall ln( _in float _digit );                                     // return log e^_digit
float __bnbcall lg( _in float _digit );                                     // return log 10^_digit
float __bnbcall lb( _in float _digit );                                     // return log 2^_digit
float __bnbcall log( _in float _base, _in float _digit );                   // return log _base^_digit
float __bnbcall exp( _in float _index );                                    // return e^_index


// exactly version
_exactly_version double __bnbcall setsign( _in const double& _digit, _in const double& _src );
_exactly_version double __bnbcall ceil( _in double _digit );
_exactly_version double __bnbcall floor( _in double _digit );
_exactly_version double __bnbcall fmod( _in double _x, _in double _y );
_exactly_version double __bnbcall modf( _in double _digit, _out double& _part );
_exactly_version double __bnbcall ldexp( _in double _digit, _in int n );
_exactly_version double __bnbcall hypot( _in double _a, _in double _b );
_exactly_version double __bnbcall frexp( _in double _digit, _out int& _index );
_exactly_version double __bnbcall extract( _in double _digit, _in int n );
_exactly_version double __bnbcall ln( _in double _digit );
_exactly_version double __bnbcall lg( _in double _digit );
_exactly_version double __bnbcall lb( _in double _digit );
_exactly_version double __bnbcall log( _in double _base, _in double _digit );
_exactly_version double __bnbcall exp( _in double _index );

// sqrt(_digit)
_return_type(double) __bnbcall _implicit_declare(_sqrt)( _in double _digit );
_return_type(float) __bnbcall _implicit_declare(_sqrt)( _in float _digit );
_overload_version(1) double __bnbcall sqrt( _in double _digit );
_overload_version(2) float __bnbcall sqrt( _in float _digit );

// trigonometric function
_return_type(double) __bnbcall _implicit_declare(_sin) _argument_list( _in double _radian );
_return_type(float) __bnbcall _implicit_declare(_sin) _argument_list( _in float _radian );
_overload_version(1) double __bnbcall sin( _in double _radian );
_overload_version(1) double __bnbcall cos( _in double _radian );
_overload_version(1) double __bnbcall tan( _in double _radian );
_overload_version(2) float __bnbcall sin( _in float _radian );
_overload_version(2) float __bnbcall cos( _in float _radian );
_overload_version(2) float __bnbcall tan( _in float _radian );

// anti-trigonometric function
_return_type(double) __bnbcall _implicit_declare(_arcsin) _argument_list( _in double _radian );
_return_type(float) __bnbcall _implicit_declare(_arcsin) _argument_list( _in float _radian );
_overload_version(1) double __bnbcall arcsin( _in double _value );
_overload_version(1) double __bnbcall arccos( _in double _value );
_overload_version(1) double __bnbcall arctan( _in double _value );
_overload_version(3) double __bnbcall arctan( _in double _oppside, _in double _adjside );
_overload_version(2) float __bnbcall arcsin( _in float _value );
_overload_version(2) float __bnbcall arccos( _in float _value );
_overload_version(2) float __bnbcall arctan( _in float _value );
_overload_version(4) float __bnbcall arctan( _in float _oppside, _in float _adjside );

// return _x^n
template<typename _Ty> inline _Ty __bnbcall _implicit_declare(_power) _argument_list( _in _Ty _x, _in int n )
{
    unsigned int _count = (unsigned int)abs(n);

    for (_Ty _product = _Ty(1); ; _x *= _x)
    {
        if (_count & 1)
            _product *= _x;

        if ( !!!(_count>>=1) )
            return ( (n < 0) ? (_Ty(1) / _product) : _product );
    }
}
_overload_version(1) double __bnbcall power( _in double _x, _in int n );
_overload_version(2) float __bnbcall power( _in float _x, _in int n );
_overload_version(3) double __bnbcall power( _in double _x, _in double n );
_overload_version(4) float __bnbcall power( _in float _x, _in float n );

unsigned int __bnbcall gcd( _in unsigned int _a, _in unsigned int _b ); // return _a and _b greatest common divisor 
unsigned int __bnbcall lcm( _in unsigned int _a, _in unsigned int _b ); // return _a and _b least common multiple

_overload_version(1) inline double __bnbcall angle_to_radian( _in double _angle ) { return (_angle * 1.74532925199432957692e-2); }
_overload_version(1) inline double __bnbcall radian_to_angle( _in double _radian ) { return (_radian * 57.2957795130823208768); }
_overload_version(2) inline float __bnbcall angle_to_radian( _in float _angle ) { return (float)angle_to_radian((double)_angle); }
_overload_version(2) inline float __bnbcall radian_to_angle( _in float _radian ) { return (float)radian_to_angle((double)_radian); }

// return n!
_overload_version(1) inline unsigned int __bnbcall factorial( _in unsigned int n )
{ unsigned int fac = 1; while ( n > 1 ) fac *= n--; return fac; }
_overload_version(2) inline unsigned long long __bnbcall factorial( _in unsigned long n )
{ unsigned long long fac = 1; while ( n > 1 ) fac *= n--; return fac; }

_bnb_space_out


#endif