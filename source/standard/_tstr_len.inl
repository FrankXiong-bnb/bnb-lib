#ifdef _declare_inside_name

inline unsigned int __bnbcall _declare_inside_name(_len)( _in const _char_t* _str )
{
    const _char_t* pos = _str;

    while ( *pos++ );

    return  (unsigned int)(pos - _str - 1);
}

inline unsigned int __bnbcall _declare_inside_name(_len)( _in const _char_t* _str, _in unsigned int maxsize )
{
    unsigned int n;

    for (n = 0; n < maxsize && *_str; ++n, ++_str);

    return n;
}

#endif