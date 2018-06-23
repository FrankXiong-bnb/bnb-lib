#ifdef _declare_inside_name

inline const void* __bnbcall _declare_inside_name(mem_chr)( const void* _ptr, int _c, unsigned int n )
{
    while ( n && (*(unsigned char *)_ptr != (unsigned char)_c) )
    {
        _ptr = (unsigned char *)_ptr + 1;
        --n;
    }

    if ( n )
        return _ptr;

    return nullptr;
}

inline void* __bnbcall _declare_inside_name(mem_chr)( void* _ptr, int _c, unsigned int n )
{
    return const_cast<void*>(mem_chr((const void*)_ptr, _c, n));
}

inline void* __bnbcall _declare_inside_name(mem_set)( void* _ptr, int _val, unsigned int n )
{
    void *start = _ptr;

    while (n--)
    {
        *(char*)_ptr = (char)_val;
        _ptr = (char*)_ptr + 1;
    }

    return(start);
}

template<typename _Ty, unsigned int _size>
inline _Ty* __bnbcall _declare_inside_name(mem_set)( _Ty (&_arr)[_size], const _Ty& _val /*= 0*/ )
{
    for (_index_t index = _size; index; _arr[--index] = _val);

    return (_arr);
}

inline void* __bnbcall _implicit_inside_name(_mem_cpy)( void* _dst, const void* _src, unsigned int n )
{
    void * ret = _dst;

    while (n--)
    {
        *(char*)_dst = *(char*)_src;
        _dst = (char*)_dst + 1;
        _src = (char*)_src + 1;
    }

    return(ret);
}

inline void* __bnbcall _implicit_inside_name(_mem_cpy)( void* _dst, const void* _src, int _c, unsigned int n )
{
    while ( n
        &&(*((char*)(_dst = (char*)_dst + 1) - 1) = *((char*)(_src = (char*)_src + 1) - 1)) != (char)_c )
        --n;

    if ( n ) return _dst;

    return nullptr;
}

inline void* __bnbcall _declare_inside_name(mem_cpy)( void* _dst, unsigned int _size, const void* _src, unsigned int n )
{
    if ( !!!(_dst && _src) )
        return _dst;

    return _implicit_inside_name(_mem_cpy)(_dst, _src, ((n<_size) ? n : _size));
}

inline void* __bnbcall _declare_inside_name(mem_cpy)( void* _dst, unsigned int _size, const void* _src, int _c, unsigned int n )
{
    if ( !!!(_dst && _src) )
        return _dst;

    return _implicit_inside_name(_mem_cpy)(_dst, _src, _c, ((n<_size) ? n : _size));
}

template<typename _Ty, unsigned int _size>
inline _Ty* __bnbcall _declare_inside_name(mem_cpy)( _Ty (&_dst)[_size], const void* _src, unsigned int n )
{
    return static_cast<_Ty*>(_declare_inside_name(mem_cpy)(_dst, _size * sizeof(_Ty), _src, n));
}

template<typename _Ty, unsigned int _size>
inline _Ty* __bnbcall _declare_inside_name(mem_cpy)( _Ty (&_dst)[_size], const void* _src, int _c, unsigned int n )
{
    return static_cast<_Ty*>(_declare_inside_name(mem_cpy)(_dst, _size * sizeof(_Ty), _src, _c, n));
}

inline void* __bnbcall _declare_inside_name(mem_move)( void* _dst, const void* _src, unsigned int n )
{
    void* _start = _dst;

    if (_dst <= _src || (char*)_dst >= ((char*)_src + n))
    {
        while (n--)
        {
            *(char*)_dst = *(char*)_src;
            _dst = (char*)_dst + 1;
            _src = (char*)_src + 1;
        }
    }
    else
    {
        _dst = (char*)_dst + n - 1;
        _src = (char*)_src + n - 1;

        while (n--)
        {
            *(char*)_dst = *(char*)_src;
            _dst = (char*)_dst - 1;
            _src = (char*)_src - 1;
        }
    }

    return (_start);
}

inline void* __bnbcall _declare_inside_name(mem_move)( void* _dst, unsigned int size, const void* _src, unsigned int n )
{
    if ( !!!(_dst && _src && size>=n) )
        return _dst;

    return _declare_inside_name(mem_move)(_dst, _src, n);
}

inline int __bnbcall _declare_inside_name(mem_cmp)( const void* _buf1, const void* _buf2, unsigned int n )
{
    if ( !!!n )
        return 0;

    while ( --n && *(char*)_buf1 == *(char*)_buf2 )
    {
        _buf1 = (char*)_buf1 + 1;
        _buf2 = (char*)_buf2 + 1;
    }

    return (int)(*((unsigned char*)_buf1) - *((unsigned char*)_buf2));
}

inline int __bnbcall _declare_inside_name(mem_icmp)( const void* _buf1, const void* _buf2, unsigned int n )
{
    int _val1 = 0, _val2 = 0;

    while (n--)
    {
        if ( (*(unsigned char *)_buf1 != *(unsigned char *)_buf2) )
            break;
        
        if ( ((_val1 = *(char*)_buf1) > 0x40) && (_val1 < 0x5b) )
            _val1 |= 0x20;

        if ( ((_val2 = *(char*)_buf2) > 0x40) && (_val2 < 0x5b) )
            _val2 |= 0x20;

        if (_val1 != _val2)
            break;

        _buf1 = (char *)_buf1 + 1;
        _buf2 = (char *)_buf2 + 1;
    }

    return (_val1 - _val2);
}

inline const wchar* __bnbcall _declare_inside_name(wmem_chr)( const wchar* _ptr, wchar wc, unsigned int n )
{
    for ( ; 0 < n; ++_ptr, --n)
        if (*_ptr == wc)
            return (_ptr);

    return (nullptr);
}

inline wchar* __bnbcall _declare_inside_name(wmem_chr)( wchar* _ptr, wchar wc, unsigned int n )
{
    return const_cast<wchar*>(_declare_inside_name(wmem_chr)(_ptr, wc, n));
}

inline int __bnbcall _declare_inside_name(wmem_cmp)( const wchar* _buf1, const wchar* _buf2, unsigned int n )
{
    for ( ; 0 < n; ++_buf1, ++_buf2, --n)
        if (*_buf1 != *_buf2)
            return ((*_buf1 < *_buf2) ? (-1) : (+1));

    return (0);
}

inline int __bnbcall _declare_inside_name(wmem_icmp)( const wchar* _buf1, const wchar* _buf2, unsigned int n )
{
    int _val1 = 0, _val2 = 0;

    for (int _inv = L'a' - L'A'; n-- && (*_buf1 == *_buf2); ++_buf1, ++_buf2)
    {
        if ( ((_val1 = *_buf1) >= L'A') && (_val1 <= L'Z') )
            _val1 += _inv;

        if ( ((_val2 = *_buf2) >= L'A') && (_val2 <= L'Z') )
            _val2 += _inv;

        if (_val1 != _val2)
            break;
    }

    return (_val1 - _val2);
}

inline wchar* __bnbcall _implicit_inside_name(_wmem_cpy)( wchar* _dst, const wchar* _src, unsigned int n )
{
    for (wchar* start = _dst; 0 < n; --n)
        *start++ = *_src++;

    return (_dst);
}

inline wchar* __bnbcall _implicit_inside_name(_wmem_cpy)( wchar* _dst, const wchar* _src, int _wc, unsigned int n )
{
    while ( n && (*_dst++ = *_src++) != _wc )
        --n;

    if ( n ) return _dst;

    return nullptr;
}

inline wchar* __bnbcall _declare_inside_name(wmem_cpy)( wchar* _dst, unsigned int size, const wchar* _src, unsigned int n )
{
    if ( !!!(_dst && _src) )
        return nullptr;

    return _implicit_inside_name(_wmem_cpy)(_dst, _src, (n<size ? n : size));
}

inline wchar* __bnbcall _declare_inside_name(wmem_cpy)( wchar* _dst, unsigned int size, const wchar* _src, int _wc, unsigned int n )
{
    if ( !!!(_dst && _src) )
        return _dst;

    return _implicit_inside_name(_wmem_cpy)(_dst, _src, _wc, (n<size ? n : size));
}

template<_size_t _size>
inline wchar* __bnbcall _declare_inside_name(wmem_cpy)( wchar (&_dst)[_size], const wchar* _src, unsigned int n )
{
    return _declare_inside_name(wmem_cpy)(_dst, _size, _src, n);
}

template<_size_t _size>
inline wchar* __bnbcall _declare_inside_name(wmem_cpy)( wchar (&_dst)[_size], const wchar* _src, int _wc, unsigned int n )
{
    return _declare_inside_name(wmem_cpy)(_dst, _size, _src, _wc, n);
}

inline wchar* __bnbcall _declare_inside_name(wmem_set)( wchar* _ptr, wchar wc, unsigned int n )
{    
    for (wchar *wp = _ptr; 0 < n; ++wp, --n)
        *wp = wc;

    return (_ptr);
}

template<unsigned int _size>
inline wchar* __bnbcall _declare_inside_name(wmem_set)( wchar (&_arr)[_size], wchar _val /*= 0*/ )
{
    return _declare_inside_name(mem_set)(_arr, _val, _size);
}

inline wchar* __bnbcall _declare_inside_name(wmem_move)( wchar* _dst, const wchar* _src, unsigned int n )
{
    wchar* _start = _dst;

    if (_dst <= _src || _dst >= (_src + n))
        while (n--)
            *_dst++ = *_src++;
    else
        for (_dst += (n - 1), _src += (n - 1); n--; )
            *_dst-- = *_src--;

    return (_start);
}

inline wchar* __bnbcall _declare_inside_name(wmem_move)( wchar* _dst, unsigned int size, const wchar* _src, unsigned int n )
{
    if ( !!!(_dst && _src && size>=n) )
        return _dst;

    return _declare_inside_name(wmem_move)(_dst, _src, n);
}

#endif