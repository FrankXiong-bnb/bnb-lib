#ifdef _declare_inside_name

#define _val_lower_upper    (L'a' - L'A')

inline unsigned int __bnbcall _declare_inside_name(_lower)( wchar_t* _wstr )
{
    unsigned int count = 0;

    for ( ; *_wstr; ++_wstr)
        if (L'A' <= *_wstr && *_wstr <= L'Z')
            *_wstr += _val_lower_upper, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_lower)( wchar_t* _wstr, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_wstr); ++_wstr )
        if (L'A' <= *_wstr && *_wstr <= L'Z')
            *_wstr += _val_lower_upper, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_upper)( wchar_t* _wstr )
{
    unsigned int count = 0;

    for ( ; *_wstr; ++_wstr)
        if (L'a' <= *_wstr && *_wstr <= L'z')
            *_wstr -= _val_lower_upper, ++count;

    return count;
}

inline unsigned int __bnbcall _declare_inside_name(_upper)( wchar_t* _wstr, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_wstr); ++_wstr )
        if (L'a' <= *_wstr && *_wstr <= L'z')
            *_wstr -= _val_lower_upper, ++count;

    return count;
}

#undef _val_lower_upper

#endif