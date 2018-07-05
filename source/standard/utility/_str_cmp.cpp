
namespace bnb
{

inline int str_cmp( const char* _str1, const char* _str2 )
{
    int _bool   = 0;

    while (!(_bool = *(unsigned char*)_str1 - *(unsigned char*)_str2) && *_str2)
        ++_str1, ++_str2;

    return _bool;
}

inline int str_cmp( const char* _str1, const char* _str2, unsigned int n )
{
    for ( unsigned int _index = 0; _index < n; ++_index, ++_str1, ++_str2)
        if (0 == *_str1 || *_str1 != *_str2)
            return (int)(*(unsigned char *)_str1 - *(unsigned char *)_str2);

    return 0;
}

inline int str_icmp( const char* _str1, const char* _str2 )
{
    int _val1, _val2;

    do{
        if ( ((_val1 = (unsigned char)(*(_str1++))) > 0x40) && (_val1 < 0x5b) )
            _val1 |= 0x20;

        if ( ((_val2 = (unsigned char)(*(_str2++))) > 0x40) && (_val2 < 0x5b) )
            _val2 |= 0x20;
    } while ( _val1 && (_val1 == _val2) );

    return (_val1 - _val2);
}

inline int str_icmp( const char* _str1, const char* _str2, unsigned int n )
{
    if( !!!n ) return 0;

    int _val1 = 0, _val2 = 0;

    do {
        if ( ((_val1 = (unsigned char)(*(_str1++))) > 0x40) && (_val1 < 0x5b) )
            _val1 |= 0x20;

        if ( ((_val2 = (unsigned char)(*(_str2++))) > 0x40) && (_val2 < 0x5b) )
            _val2 |= 0x20;
    } while ( --n && _val1 && (_val1 == _val2) );

    return (_val1 - _val2);
}

}
