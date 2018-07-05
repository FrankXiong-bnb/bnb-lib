
template<typename _char_t>
inline unsigned int t_str_len(const _char_t* _str)
{
    const _char_t* pos = _str;

    while (*pos++);

    return  (unsigned int)(pos - _str - 1);
}

template<typename _char_t>
inline unsigned int t_str_len(const _char_t* _str, unsigned int maxsize)
{
    unsigned int n;

    for (n = 0; n < maxsize && *_str; ++n, ++_str);

    return n;
}
