
template<typename _char_t>
inline _char_t* _t_str_cpy(_char_t* _dst, const _char_t* _src)
{
    _char_t* pos = _dst;

    while (*pos++ = *_src++);

    return (_dst);
}


template<typename _char_t>
inline _char_t* _t_str_cpy(_char_t* _dst, const _char_t* _src, unsigned int n)
{
    _char_t *pos = _dst;

    while (n && (*_dst++ = *_src++)) --n;

    if (n)
        while (--n)
            *_dst++ = 0;

    return (pos);
}

template<typename _char_t>
inline unsigned int t_str_cpy(_char_t* _dst, unsigned int _size, const _char_t* _src)
{
    if (!!!(_dst && _src && 0 < _size)) return 0;

    unsigned int valid = _size;

    while ((--valid) && (*_dst++ = *_src++));

    if (!valid) *_dst = 0;

    return (_size - valid - 1);
}

template<typename _char_t>
inline unsigned int t_str_cpy(_char_t* _dst, unsigned int _size, const _char_t* _src, unsigned int n)
{
    if (!!!(_dst && _src && 0 < _size && 0 < n)) return 0;

    unsigned int valid = _size;

    while ((--valid) && n && (*_dst++ = *_src++)) n--;

    if (!valid || !n) *_dst = 0;

    return (_size - valid - 1);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_cpy(_char_t(&_dst)[_size], const _char_t* _src)
{
    return t_str_cpy(_dst, _size, _src);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_cpy(_char_t(&_dst)[_size], const _char_t* _src, unsigned int n)
{
    return t_str_cpy(_dst, _size, _src, n);
}
