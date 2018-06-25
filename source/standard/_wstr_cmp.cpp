
namespace bnb
{

inline int wstr_cmp(const wchar_t* _str1, const wchar_t* _str2)
{
    int _bool = 0;

    while (!(_bool = (int)(*_str1 - *_str2)) && *_str2)
        ++_str1, ++_str2;

    if (_bool < 0) return -1;
    if (_bool > 0) return +1;

    return  _bool;
}

inline int wstr_cmp(const wchar_t* _str1, const wchar_t* _str2, unsigned int n)
{
    if (!!!n) return 0;

    for (; --n && *_str1 && *_str1 == *_str2; ++_str1, ++_str2);

    return (int)(*_str1 - *_str2);
}


inline int wstr_icmp(const wchar_t* _str1, const wchar_t* _str2)
{
    int _val1, _val2;

    do {
        if (((_val1 = (*_str1++)) >= L'A') && (_val1 <= L'Z'))
            _val1 += (L'a' - L'A');

        if (((_val2 = (*_str2++)) >= L'A') && (_val2 <= L'Z'))
            _val2 += (L'a' - L'A');
    } while (_val1 && (_val1 == _val2));

    return (_val1 - _val2);
}

inline int wstr_icmp(const wchar_t* _str1, const wchar_t* _str2, unsigned int n)
{
    if (!!!n) return 0;

    int _val1 = 0, _val2 = 0;

    do {
        if (((_val1 = (*_str1++)) >= L'A') && (_val1 <= L'Z'))
            _val1 += (L'a' - L'A');

        if (((_val2 = (*_str2++)) >= L'A') && (_val2 <= L'Z'))
            _val2 += (L'a' - L'A');
    } while (--n && _val1 && (_val1 == _val2));

    return (_val1 - _val2);
}

}
