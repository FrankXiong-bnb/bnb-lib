
namespace bnb
{

inline unsigned int str_lower( char* _str )
{
    unsigned int count = 0;

    for ( ; *_str; ++_str)
        if (0x40 < *_str && *_str < 0x5b)
            *_str |= 0x20, ++count;

    return count;
}

inline unsigned int str_lower( char* _str, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_str); ++_str )
        if (0x40 < *_str && *_str < 0x5b)
            *_str |= 0x20, ++count;

    return count;
}

inline unsigned int str_upper( char* _str )
{
    unsigned int count = 0;

    for ( ; *_str; ++_str)
        if (0x60 < *_str && *_str < 0x7b)
            *_str &= 0xdf, ++count;

    return count;
}

inline unsigned int str_upper( char* _str, unsigned int n )
{
    unsigned int count = 0;

    for ( ; (n-- && *_str); ++_str )
        if (0x60 < *_str && *_str < 0x7b)
            *_str &= 0xdf, ++count;

    return count;
}

}
