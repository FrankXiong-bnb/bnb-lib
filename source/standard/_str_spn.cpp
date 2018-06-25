
namespace bnb
{

inline unsigned int _str_map( unsigned char (&_map)[32], const char* _src)
{
    unsigned int count = 0;

    for (const unsigned char* ctrl = (const unsigned char*)_src ; *ctrl; ++ctrl, ++count)
        _map[*ctrl >> 3] |= (1 << (*ctrl & 7));

    return count;
}

inline unsigned int _str_first_has( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _str_map(_map, _src);

    unsigned int _pos=0;

    for ( _map[0] |= 1; !(_map[*_dst >> 3] & (1 << (*_dst & 7))); ++_dst, ++_pos);

    return (_pos);
}

inline unsigned int _str_first_not( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _str_map(_map, _src);

    unsigned int _pos=0;

    for ( ; (_map[*_dst >> 3] & (1 << (*_dst & 7))); ++_pos, ++_dst);

    return (_pos);
}

inline const char* str_first_has( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _str_map(_map, _src);

    for ( ; *_dst; ++_dst)
        if( (_map[*_dst >> 3] & (1 << (*_dst & 7))) )
            return _dst;

    return nullptr;
}

inline char* str_first_has( char* _dst, const char* _src )
{
    return (const_cast<char*>(str_first_has((const char*)_dst, _src)));
}

inline const char* str_first_not( const char* _dst, const char* _src )
{
    unsigned char _map[32] = { 0 };

    _str_map(_map, _src);

    for ( ; ; ++_dst)
        if( !!!(_map[*_dst >> 3] & (1 << (*_dst & 7))) )
            break;

    return (*_dst ? _dst : nullptr);
}

inline char* str_first_not( char* _dst, const char* _src )
{
    return (const_cast<char*>(str_first_not((const char*)_dst, _src)));
}

}
