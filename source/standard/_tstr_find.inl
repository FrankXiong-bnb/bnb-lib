
template<typename _char_t>
inline const _char_t* t_str_chr(const _char_t* _src, int _key)
{
    while (*_src && *_src != _key)
        ++_src;

    if (*_src == _key)
        return (_src);

    return (nullptr);
}

template<typename _char_t>
inline _char_t* t_str_chr(_char_t* _src, int _key)
{
    return (const_cast<_char_t*>(t_str_chr((const _char_t*)_src, _key)));
}

template<typename _char_t>
inline const _char_t* t_str_rchr(const _char_t* _src, int _key)
{
    const _char_t *start = _src;

    while (*_src++);

    while (--_src != start && *_src != _key);

    if (*_src == _key)
        return (_src);

    return (nullptr);
}

template<typename _char_t>
inline _char_t* t_str_rchr(_char_t* _src, int _key)
{
    return (const_cast<_char_t*>(t_str_rchr((const _char_t*)_src, _key)));
}

template<typename _char_t>
inline const _char_t* t_str_str(const _char_t* _dst, const _char_t* _src)
{
    for (const _char_t* start = _dst; *start; ++start)
    {
        const _char_t* s2 = _src;

        for (const _char_t* s1 = start; (*s1 && *s2 && !(*s1 - *s2)); ++s1, ++s2);

        if (!*s2) return (start);
    }

    return (nullptr);
}

template<typename _char_t>
inline _char_t* t_str_str(_char_t* _dst, const _char_t* _src)
{
    return (const_cast<_char_t*>(t_str_str((const _char_t*)_dst, _src)));
}
