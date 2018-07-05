
template<typename _char_t>
inline _char_t* _t_str_set(_char_t* _str, int _val)
{
    _char_t* start = _str;

    while (*_str) *_str++ = _val;

    return (start);
}

template<typename _char_t>
inline _char_t* _t_str_set(_char_t* _str, int _val, unsigned int n)
{
    _char_t* start = _str;

    while (n-- && *_str) *_str++ = _val;

    return (start);
}

template<typename _char_t>
inline unsigned int t_str_set(_char_t* _str, unsigned int _size, int _val)
{
    if (!!!(_str && _size && _size < (1 << ((sizeof(unsigned int) << 3) - 2)))) return 0;

    unsigned int valid = _size;

    while (--valid && *_str) *_str++ = _val;

    _size -= (valid + 1);

    do { *_str++ = 0; } while (valid--);

    return (_size);
}

template<typename _char_t>
inline unsigned int t_str_set(_char_t* _str, unsigned int _size, int _val, unsigned int n)
{
    if (!!!(_str && _size && _size < (1 << ((sizeof(unsigned int) << 3) - 2)))) return 0;

    unsigned int valid = _size;

    for (; (--valid && n && *_str); *_str++ = _val, --n);

    _size -= (valid + 1);

    do { *_str++ = 0; } while (valid--);

    return (_size);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_set(_char_t(&_str)[_size], int _val)
{
    return t_str_set(_str, _size, _val);
}

template<typename _char_t, unsigned int _size>
inline unsigned int t_str_set(_char_t(&_str)[_size], int _val, unsigned int n)
{
    return t_str_set(_str, _size, _val, n);
}
