
template<typename _char_t>
inline _char_t* _t_str_cat(_char_t* _dst, const _char_t* _src)
{
    _char_t* pos = _dst;

    while (*pos) ++pos;

    while (*pos++ = *_src++);

    return _dst;
}

template<typename _char_t>
inline _char_t* _t_str_cat(_char_t* _dst, const _char_t* _src, unsigned int n)
{
    _char_t *start = _dst;

    while (*_dst) _dst++;

    while (n--)
        if (!(*_dst++ = *_src++))
            return (start);

    *_dst = 0;

    return (start);
}

template<typename _char_t>
inline unsigned int t_str_cat(_char_t* _dst, unsigned int _size, const _char_t* _src)
{
    if (!!!(_dst && _src && 0 < _size)) return 0;

    unsigned int valid = _size;

    for (; (valid && *_dst); --valid, ++_dst);

    if (!!!valid) return 0;

    while ((--valid) && (*_dst++ = *_src++));

    if (!valid) *_dst = 0;

    return (_size - valid - 1);
}

template<typename _char_t>
inline unsigned int t_str_cat(_char_t* _dst, unsigned int _size, const _char_t* _src, unsigned int n)
{
    if (!!!(_dst && _src && 0 < _size && 0 < n)) return 0;

    unsigned int valid = _size;

    for (; (valid && *_dst); --valid, ++_dst);

    if (!!!valid) return 0;

    while ((--valid) && n && (*_dst++ = *_src++)) n--;

    if (!valid || !n) *_dst = 0;

    return (_size - valid - 1);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_cat(_char_t(&_dst)[_size], const _char_t* _src)
{
    return t_str_cat(_dst, _size, _src);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_cat(_char_t(&_dst)[_size], const _char_t* _src, unsigned int n)
{
    return t_str_cat(_dst, _size, _src, n);
}
