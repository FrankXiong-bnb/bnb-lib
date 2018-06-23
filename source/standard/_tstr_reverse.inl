#ifdef _declare_inside_name

inline _char_t* __bnbcall _declare_inside_name(_reverse)( _char_t* _str )
{
    _char_t *right = _str;

    while (*right++);
    right -= 2;

    for (_char_t* left = _str; left < right; ++left, --right)
        *left ^= *right ^= *left ^= *right;

    return (_str);
}

inline _char_t* __bnbcall _declare_inside_name(_reverse)( _char_t* _str, unsigned int n )
{
    _char_t *right = _str;

    while ( *right && n ) ++right, --n;
    --right;

    for (_char_t* left = _str; left < right; ++left, --right)
        *left ^= *right ^= *left ^= *right;

    return (_str);
} 

#endif