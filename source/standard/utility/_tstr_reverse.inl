
template<typename _char_t>
inline _char_t* t_str_reverse(_char_t* _str)
{
    _char_t *right = _str;

    while (*right++);
    right -= 2;

    for (_char_t* left = _str; left < right; ++left, --right)
        *left ^= *right ^= *left ^= *right;

    return (_str);
}

template<typename _char_t>
inline _char_t* t_str_reverse(_char_t* _str, unsigned int n)
{
    _char_t *right = _str;

    while (*right && n) ++right, --n;
    --right;

    for (_char_t* left = _str; left < right; ++left, --right)
        *left ^= *right ^= *left ^= *right;

    return (_str);
}
