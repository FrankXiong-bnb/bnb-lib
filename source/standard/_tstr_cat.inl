#ifdef _declare_inside_name

inline _char_t* __bnbcall _implicit_inside_name(_cat)( _char_t* _dst, const _char_t* _src )
{
    _char_t* pos = _dst;

    while (*pos) ++pos;

    while (*pos++  = *_src++);

    return _dst;
}

inline _char_t* __bnbcall _implicit_inside_name(_cat)( _char_t* _dst, const _char_t* _src, unsigned int n )
{
    _char_t *start = _dst;

    while (*_dst) _dst++;

    while (n--)
        if (!(*_dst++ = *_src++))
            return (start);

    *_dst = 0;

    return (start);
}

inline unsigned int __bnbcall _declare_inside_name(_cat)( _char_t* _dst, unsigned int _size, const _char_t* _src)
{
    if( !!!(_dst && _src && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    for ( ; (valid && *_dst); --valid, ++_dst);

    if( !!!valid ) return 0;

    while ( (--valid) && (*_dst++ = *_src++) );

    if ( !valid ) *_dst = 0;

    return (_size - valid - 1);
}

inline unsigned int __bnbcall _declare_inside_name(_cat)( _char_t* _dst, unsigned int _size, const _char_t* _src, unsigned int n )
{
    if( !!!(_dst && _src && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    for ( ; (valid && *_dst); --valid, ++_dst);

    if( !!!valid ) return 0;

    while ( (--valid) && n && (*_dst++ = *_src++) ) n--;

    if ( !valid || !n ) *_dst = 0;

    return (_size - valid - 1);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_cat)( _char_t (&_dst)[_size], const _char_t* _src )
{
    return _declare_inside_name(_cat)(_dst, _size, _src);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_cat)( _char_t (&_dst)[_size], const _char_t* _src, unsigned int n )
{
    return _declare_inside_name(_cat)(_dst, _size, _src, n);
}

#endif