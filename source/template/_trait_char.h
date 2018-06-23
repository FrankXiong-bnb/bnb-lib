#ifndef __bnb_trait_char_h_
#define __bnb_trait_char_h_


_bnb_space_in

template<typename _elemT, typename _intT>
struct base_trait_char 
{
    typedef _intT   int_type;
    typedef _elemT  char_type;
    typedef _elemT* pchar_type;
    typedef _elemT& rchar_type;

    typedef unsigned int pos_type;
    typedef unsigned int size_type;

    typedef base_trait_char<_elemT, _intT>  base_trait_char_t;

    static size_type __cdecl size(_in const _elemT* _first)
    {
        size_t _size;

        for (_size = 0; !equal(*_first, _elemT()); ++_first, ++_size);

        return (_size);
    }

    static void __cdecl assign(_out _elemT& _dst, _in const _elemT& _src)
    {
        _dst = _src;
    }

    static _elemT* __cdecl assign(_out _elemT* _dst, _in const _elemT& _ch, _in size_type _n)
    {
        _elemT* start = _dst;

        for ( ; _n; --_n, ++_dst)
            *_dst = _ch;

        return start;
    }

    static int __cdecl compare(_in const _elemT* _e1, _in const _elemT* _e2, _in size_type _n)
    {
        for ( ; 0 < _n; --_n, ++_e1, ++_e2)
            if (!equal(*_e1, *_e2))
                return (less(*_e1, *_e2) ? -1 : +1);

        return (0);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        _elemT* start = _dst;

        for (; 0 < _n; --_n, ++_dst, ++_src)
            *_dst = *_src;

        return (start);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in size_type _size, _in const _elemT* _src, _in size_type _n)
    {
        _bnb_assert_return((_size >= _n), nullptr);

        return copy(_dst, _src, _n);
    }

    static const _elemT* __cdecl find(_in const _elemT* _first, _in size_type _size, const _elemT& _ch)
    {
        for ( ; 0 < _size; --_size, ++_first)
            if ( equal(*_first, _ch) )
                return (_first);

        return (nullptr);
    }

    static _elemT* __cdecl move(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        _elemT *_next = _dst;

        if (_src < _next && _next < _src + _n)
            for (_next += _n, _src += _n; 0 < _n; --_n)
                assign(*--_next, *--_src);
        else
            for (; 0 < _n; --_n, ++_next, ++_src)
                assign(*_next, *_src);

        return (_dst);
    }

    static bool __cdecl equal(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left == _right);
    }

    static bool __cdecl less(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left < _right);
    }

    static _elemT __cdecl to_char_type(_in const int_type& _meta)
    {
        return ((_elemT)_meta);
    }

    static int_type __cdecl to_int_type(_in const _elemT& _ch)
    {
        return ((int_type)_ch);
    }

    static bool __cdecl eq_int_type(_in const int_type& _left, _in const int_type& _right)
    {
        return (_left == _right);
    }

};  // template<typename _elemT, typename _intT> struct base_trait_char 


template<class _elemT>
struct trait_char : public base_trait_char<_elemT, long> 
{
    typedef trait_char<_elemT>  trait_char_t;
};

template<>
struct trait_char<unsigned int> : public base_trait_char<unsigned int, unsigned long>
{
    typedef trait_char<unsigned int>  trait_char_t;
};

template<>
struct trait_char<unsigned short>
{
    typedef unsigned short  _elemT;
    typedef unsigned short  int_type;
    typedef _elemT          char_type;
    typedef _elemT*         pchar_type;
    typedef _elemT&         rchar_type;

    typedef unsigned int    pos_type;
    typedef unsigned int    size_type;

    typedef trait_char<_elemT>  trait_char_t;

    static size_type __cdecl size(_in const _elemT* _first)
    {
        const _elemT* pos = _first;

        while ( *pos++ );

        return  (_size_t)(pos - _first - 1);
    }

    static void __cdecl assign(_out _elemT& _dst, _in const _elemT& _src)
    {
        _dst = _src;
    }

    static _elemT* __cdecl assign(_out _elemT* _dst, _in const _elemT& _ch, _in size_type _n)
    {
        for (_elemT* start = _dst; _n; --_n, ++start)
            *start = _ch;

        return _dst;
    }

    static int __cdecl compare(_in const _elemT* _e1, _in const _elemT* _e2, _in size_type _n)
    {
        for ( ; 0 < _n; --_n, ++_e1, ++_e2)
            if (!equal(*_e1, *_e2))
                return (less(*_e1, *_e2) ? -1 : +1);

        return (0);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        for (_elemT* start = _dst; 0 < _n; --_n)
            *start++ = *_src++;

        return (_dst);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in size_type _size, _in const _elemT* _src, _in size_type _n)
    {
        _bnb_assert_return( (_dst && _src && _n), _dst);

        size_type _count = _size < _n ? _size : _n;

        return copy(_dst, _src, _count);
    }

    static const _elemT* __cdecl find(_in const _elemT* _first, _in size_type _size, const _elemT& _ch)
    {
        for ( ; 0 < _size; --_size, ++_first)
            if ( equal(*_first, _ch) )
                return (_first);

        return (nullptr);
    }

    static _elemT* __cdecl move(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        _elemT *_next = _dst;

        if (_src < _next && _next < _src + _n)
            for (_next += _n, _src += _n; 0 < _n; --_n)
                assign(*--_next, *--_src);
        else
            for (; 0 < _n; --_n, ++_next, ++_src)
                assign(*_next, *_src);

        return (_dst);
    }

    static bool __cdecl equal(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left == _right);
    }

    static bool __cdecl less(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left < _right);
    }

    static _elemT __cdecl to_char_type(_in const int_type& _meta)
    {
        return (_meta);
    }

    static int_type __cdecl to_int_type(_in const _elemT& _ch)
    {
        return (_ch);
    }

    static bool __cdecl eq_int_type(_in const int_type& _left, _in const int_type& _right)
    {
        return (_left == _right);
    }
};

template<>
struct trait_char<wchar_t>
{
    typedef wchar_t         _elemT;
    typedef unsigned short  int_type;
    typedef _elemT          char_type;
    typedef _elemT*         pchar_type;
    typedef _elemT&         rchar_type;

    typedef unsigned int    pos_type;
    typedef unsigned int    size_type;

    typedef trait_char<_elemT>  trait_char_t;

    static size_type __cdecl size(_in const _elemT* _first)
    {
        const _elemT* pos = _first;

        while ( *pos++ );

        return  (_size_t)(pos - _first - 1);
    }

    static void __cdecl assign(_out _elemT& _dst, _in const _elemT& _src)
    {
        _dst = _src;
    }

    static _elemT* __cdecl assign(_out _elemT* _dst, _in const _elemT& _ch, _in size_type _n)
    {
        for (_elemT* start = _dst; _n; --_n, ++start)
            *start = _ch;

        return _dst;
    }

    static int __cdecl compare(_in const _elemT* _e1, _in const _elemT* _e2, _in size_type _n)
    {
        for ( ; 0 < _n; --_n, ++_e1, ++_e2)
            if (!equal(*_e1, *_e2))
                return (less(*_e1, *_e2) ? -1 : +1);

        return (0);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        for (_elemT* start = _dst; 0 < _n; --_n)
            *start++ = *_src++;

        return (_dst);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in size_type _size, _in const _elemT* _src, _in size_type _n)
    {
        _bnb_assert_return( (_dst && _src && _n), _dst);

        size_type _count = _size < _n ? _size : _n;

        return copy(_dst, _src, _count);
    }

    static const _elemT* __cdecl find(_in const _elemT* _first, _in size_type _size, const _elemT& _ch)
    {
        for ( ; 0 < _size; --_size, ++_first)
            if ( equal(*_first, _ch) )
                return (_first);

        return (nullptr);
    }

    static _elemT* __cdecl move(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        _elemT *_next = _dst;

        if (_src < _next && _next < _src + _n)
            for (_next += _n, _src += _n; 0 < _n; --_n)
                assign(*--_next, *--_src);
        else
            for (; 0 < _n; --_n, ++_next, ++_src)
                assign(*_next, *_src);

        return (_dst);
    }

    static bool __cdecl equal(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left == _right);
    }

    static bool __cdecl less(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left < _right);
    }

    static _elemT __cdecl to_char_type(_in const int_type& _meta)
    {
        return ((_elemT)_meta);
    }

    static int_type __cdecl to_int_type(_in const _elemT& _ch)
    {
        return ((int_type)_ch);
    }

    static bool __cdecl eq_int_type(_in const int_type& _left, _in const int_type& _right)
    {
        return (_left == _right);
    }
};

template<>
struct trait_char<char>
{
    typedef char    _elemT;
    typedef int     int_type;
    typedef _elemT  char_type;
    typedef _elemT* pchar_type;
    typedef _elemT& rchar_type;

    typedef unsigned int    pos_type;
    typedef unsigned int    size_type;

    typedef trait_char<_elemT>  trait_char_t;

    static size_type __cdecl size(_in const _elemT* _first)
    {
        const _elemT* pos = _first;

        while ( *pos++ );

        return  (_size_t)(pos - _first - 1);
    }

    static void __cdecl assign(_out _elemT& _dst, _in const _elemT& _src)
    {
        _dst = _src;
    }

    static _elemT* __cdecl assign(_out _elemT* _dst, _in const _elemT& _ch, _in size_type _n)
    {
        for (_elemT* start = _dst; _n; --_n, ++start)
            *start = _ch;

        return _dst;
    }

    static int __cdecl compare(_in const _elemT* _e1, _in const _elemT* _e2, _in size_type _n)
    {
        for ( ; 0 < _n; --_n, ++_e1, ++_e2)
            if ( *_e1 != *_e2 )
                return (int)(*_e1 - *_e2);

        return (0);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        for (_elemT* start = _dst; 0 < _n; --_n)
            *start++ = *_src++;

        return (_dst);
    }

    static _elemT* __cdecl copy(_out _elemT* _dst, _in size_type _size, _in const _elemT* _src, _in size_type _n)
    {
        _bnb_assert_return( (_dst && _src && _n), _dst);

        size_type _count = _size < _n ? _size : _n;

        return copy(_dst, _src, _count);
    }

    static const _elemT* __cdecl find(_in const _elemT* _first, _in size_type _size, const _elemT& _ch)
    {
        for ( ; 0 < _size; --_size, ++_first)
            if ( equal(*_first, _ch) )
                return (_first);

        return (nullptr);
    }

    static _elemT* __cdecl move(_out _elemT* _dst, _in const _elemT* _src, _in size_type _n)
    {
        _elemT *_next = _dst;

        if (_src < _next && _next < _src + _n)
            for (_next += _n, _src += _n; 0 < _n; --_n)
                assign(*--_next, *--_src);
        else
            for (; 0 < _n; --_n, ++_next, ++_src)
                assign(*_next, *_src);

        return (_dst);
    }

    static bool __cdecl equal(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left == _right);
    }

    static bool __cdecl less(_in const _elemT& _left, _in const _elemT& _right)
    {
        return (_left < _right);
    }

    static _elemT __cdecl to_char_type(_in const int_type& _meta)
    {
        return ((_elemT)_meta);
    }

    static int_type __cdecl to_int_type(_in const _elemT& _ch)
    {
        return ((unsigned char)_ch);
    }

    static bool __cdecl eq_int_type(_in const int_type& _left, _in const int_type& _right)
    {
        return (_left == _right);
    }
};


_bnb_space_out


#endif