#ifdef _declare_inside_name

inline _char_t* __bnbcall _implicit_inside_name(_set)( _char_t* _str, int _val )
{
    _char_t* start = _str;

    while (*_str) *_str++ = _val;

    return (start);
}

inline _char_t* __bnbcall _implicit_inside_name(_set)( _char_t* _str, int _val, unsigned int n )
{
    _char_t* start = _str;

    while (n-- && *_str) *_str++ = _val;

    return (start);
}

inline unsigned int __bnbcall _declare_inside_name(_set)( _char_t* _str, unsigned int _size, int _val )
{
    if( !!!(_str && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    while ( --valid && *_str ) *_str++ = _val;

    _size -= (valid + 1);

    do { *_str++ = 0; } while ( valid-- );

    return (_size);
}

inline unsigned int __bnbcall _declare_inside_name(_set)( _char_t* _str, unsigned int _size, int _val, unsigned int n )
{
    if( !!!(_str && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    for ( ; ( --valid && n && *_str ); *_str++ = _val, --n);

    _size -= (valid + 1);

    do { *_str++ = 0; } while ( valid-- );

    return (_size);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_set)( _char_t (&_str)[_size], int _val )
{
    return _declare_inside_name(_set)(_str, _size, _val);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_set)( _char_t (&_str)[_size], int _val, unsigned int n )
{
    return _declare_inside_name(_set)(_str, _size, _val, n);
}

#endif