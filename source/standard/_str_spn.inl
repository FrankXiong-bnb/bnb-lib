#ifdef _declare_inside_name

inline unsigned int __bnbcall _implicit_inside_name(_map)( unsigned char (&_map)[32], const char* _src)
{
    unsigned int count = 0;

    for (const unsigned char* ctrl = (const unsigned char*)_src ; *ctrl; ++ctrl, ++count)
        _map[*ctrl >> 3] |= (1 << (*ctrl & 7));

    return count;
}

inline unsigned int __bnbcall _implicit_inside_name(_first_has)( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _implicit_inside_name(_map)(_map, _src);

    unsigned int _pos=0;

    for ( _map[0] |= 1; !(_map[*_dst >> 3] & (1 << (*_dst & 7))); ++_dst, ++_pos);

    return (_pos);
}

inline unsigned int __bnbcall _implicit_inside_name(_first_not)( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _implicit_inside_name(_map)(_map, _src);

    unsigned int _pos=0;

    for ( ; (_map[*_dst >> 3] & (1 << (*_dst & 7))); ++_pos, ++_dst);

    return (_pos);
}

inline const char* __bnbcall _declare_inside_name(_first_has)( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _implicit_inside_name(_map)(_map, _src);

    for ( ; *_dst; ++_dst)
        if( (_map[*_dst >> 3] & (1 << (*_dst & 7))) )
            return _dst;

    return nullptr;
}

inline char* __bnbcall _declare_inside_name(_first_has)( char* _dst, const char* _src )
{
    return (const_cast<char*>(_declare_inside_name(_first_has)((const char*)_dst, _src)));
}

inline const char* __bnbcall _declare_inside_name(_first_not)( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _implicit_inside_name(_map)(_map, _src);

    for ( ; ; ++_dst)
        if( !!!(_map[*_dst >> 3] & (1 << (*_dst & 7))) )
            break;

    return (*_dst ? _dst : nullptr);
}

inline char* __bnbcall _declare_inside_name(_first_not)( char* _dst, const char* _src )
{
    return (const_cast<char*>(_declare_inside_name(_first_not)((const char*)_dst, _src)));
}

#endif