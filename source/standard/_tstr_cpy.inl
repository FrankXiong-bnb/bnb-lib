#ifdef _declare_inside_name

inline _char_t* __bnbcall _implicit_inside_name(_cpy)( _char_t* _dst, const _char_t* _src )
{
    _char_t* pos = _dst;

    while (*pos++  = *_src++);

    return (_dst);
}


inline _char_t* __bnbcall _implicit_inside_name(_cpy)( _char_t* _dst, const _char_t* _src, unsigned int n )
{
    _char_t *pos = _dst;

    while (n && (*_dst++ = *_src++)) --n;

    if (n)
        while (--n)
            *_dst++ = 0;

    return (pos);
}

inline unsigned int __bnbcall _declare_inside_name(_cpy)( _char_t* _dst, unsigned int _size, const _char_t* _src )
{
    if( !!!(_dst && _src && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    while ( (--valid) && (*_dst++ = *_src++) );

    if ( !valid ) *_dst = 0;

    return (_size - valid - 1);
}

inline unsigned int __bnbcall _declare_inside_name(_cpy)( _char_t* _dst, unsigned int _size, const _char_t* _src, unsigned int n )
{
    if( !!!(_dst && _src && _size && _size < (1<<((sizeof(unsigned int)<<3)-2))) ) return 0;

    unsigned int valid = _size;

    while ( (--valid) && n && (*_dst++ = *_src++) ) n--;

    if ( !valid || !n ) *_dst = 0;

    return (_size - valid - 1);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_cpy)( _char_t (&_dst)[_size], const _char_t* _src )
{
    return _declare_inside_name(_cpy)(_dst, _size, _src);
}

template<unsigned int _size>
inline unsigned int __bnbcall _declare_inside_name(_cpy)( _char_t (&_dst)[_size], const _char_t* _src, unsigned int n )
{
    return _declare_inside_name(_cpy)(_dst, _size, _src, n);
}

#endif