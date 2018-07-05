
template<typename _IterT, typename _Ty>
inline _IterT Find(_IterT first, _IterT last, _Ty val)
{
    for ( ; first != last; ++first)
        if ( *first == val)
            break;

    return first;
}

inline const char* Find(const char* first, const char* last, int val)
{
    for ( ; first != last; ++first)
        if ( *first == val)
            break;

    return first;
}

inline const signed char* Find(const signed char* first, const signed char* last, int val)
{
    for ( ; first != last; ++first)
        if ( *first == val)
            break;

    return first;
}

inline const unsigned char* Find(const unsigned char* first, const unsigned char* last, int val)
{
    for ( ; first != last; ++first)
        if ( *first == val)
            break;

    return first;
}

template<typename _IterT, typename _FuncT>
inline _IterT FindIf(_IterT first, _IterT last, _FuncT pfun)
{
    for (; first != last; ++first)
        if (pfun(*first))
            break;

    return first;
}
