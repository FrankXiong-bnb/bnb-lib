#ifdef _declare_inside_name

inline unsigned int __bnbcall _declare_inside_name(_lower)( char* _str )
{
    unsigned int count = 0;

    for ( ; *_str; ++_str)
        if (0x40 < *_str && *_str < 0x5b)
            *_str |= 0x20, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_lower)( char* _str, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_str); ++_str )
        if (0x40 < *_str && *_str < 0x5b)
            *_str |= 0x20, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_upper)( char* _str )
{
    unsigned int count = 0;

    for ( ; *_str; ++_str)
        if (0x60 < *_str && *_str < 0x7b)
            *_str &= 0xdf, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_upper)( char* _str, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_str); ++_str )
        if (0x60 < *_str && *_str < 0x7b)
            *_str &= 0xdf, ++count;

    return count;
}

#endif