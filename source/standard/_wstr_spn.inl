#ifdef _declare_inside_name

inline const wchar_t* __bnbcall _declare_inside_name(_first_has) ( const wchar_t* _src, const wchar_t* ctrl)
{
    for ( ; *_src; ++_src)
        for (const wchar_t* wptr = ctrl; *wptr; ++wptr)
            if (*wptr == *_src)
                return (_src);

    return nullptr;
}

inline wchar_t* __bnbcall _declare_inside_name(_first_has)( wchar_t* _dst, const wchar_t* _src )
{
    return (const_cast<wchar_t*>(_declare_inside_name(_first_has)((const wchar_t*)_dst, _src)));
}

inline const wchar_t* __bnbcall _declare_inside_name(_first_not) ( const wchar_t* _src, const wchar_t* ctrl)
{
    for ( ; *_src; ++_src)
        for (const wchar_t* wptr = ctrl; *wptr != *_src; ++wptr)
            if (0 == *wptr)
                return (_src);

    return nullptr;
}

inline wchar_t* __bnbcall _declare_inside_name(_first_not)( wchar_t* _dst, const wchar_t* _src )
{
    return (const_cast<wchar_t*>(_declare_inside_name(_first_not)((const wchar_t*)_dst, _src)));
}

#endif