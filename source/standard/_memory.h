#ifndef ____bnb_Memory_H_
#define ____bnb_Memory_H_

namespace bnb
{

    inline const void* mem_chr(const void* _ptr, int _c, unsigned int n)
    {
        while (n && (*(unsigned char *)_ptr != (unsigned char)_c))
        {
            _ptr = (unsigned char *)_ptr + 1;
            --n;
        }

        return 0 < n ? _ptr : nullptr;
    }

    inline void* mem_chr(void* _ptr, int _c, unsigned int n)
    {
        return const_cast<void*>(mem_chr((const void*)_ptr, _c, n));
    }

    inline void* mem_set(void* _ptr, int _val, unsigned int n)
    {
        void *start = _ptr;

        while (n--)
        {
            *(char*)_ptr = (char)_val;
            _ptr = (char*)_ptr + 1;
        }

        return(start);
    }

    template<typename _Ty, unsigned int _size> inline _Ty* mem_set(_Ty(&_arr)[_size], const _Ty& _val = 0)
    {
        for (_index_t index = _size; index; _arr[--index] = _val);

        return (_arr);
    }
    
    inline void* _mem_cpy(void* _dst, const void* _src, unsigned int n)
    {
        void * ret = _dst;

        while (n--)
        {
            *(char*)_dst = *(char*)_src;
            _dst = (char*)_dst + 1;
            _src = (char*)_src + 1;
        }

        return (ret);
    }

    inline void* _mem_cpy(void* _dst, const void* _src, int _c, unsigned int n)
    {
        while (n
            && (*((char*)(_dst = (char*)_dst + 1) - 1) = *((char*)(_src = (char*)_src + 1) - 1)) != (char)_c)
            --n;

        return 0 < n ? _dst : nullptr;
    }

    inline void* mem_cpy(void* _dst, unsigned int _size, const void* _src, unsigned int n)
    {
        if (!!!(_dst && _src))
            return _dst;

        return _mem_cpy(_dst, _src, ((n < _size) ? n : _size));
    }

    inline void* mem_cpy(void* _dst, unsigned int _size, const void* _src, int _c, unsigned int n)
    {
        if (!!!(_dst && _src))
            return _dst;

        return _mem_cpy(_dst, _src, _c, ((n < _size) ? n : _size));
    }

    template<typename _Ty, unsigned int _size> inline _Ty* mem_cpy(_Ty(&_dst)[_size], const void* _src, unsigned int n)
    {
        return static_cast<_Ty*>(mem_cpy(_dst, _size * sizeof(_Ty), _src, n));
    }

    template<typename _Ty, unsigned int _size> inline _Ty* mem_cpy(_Ty(&_dst)[_size], const void* _src, int _c, unsigned int n)
    {
        return static_cast<_Ty*>(mem_cpy(_dst, _size * sizeof(_Ty), _src, _c, n));
    }

    inline void* mem_move(void* _dst, const void* _src, unsigned int n)
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

    inline void* mem_move(void* _dst, unsigned int _size, const void* _src, unsigned int n)
    {
        if (!!!(_dst && _src && _size >= n))
            return _dst;

        return mem_move(_dst, _src, n);
    }

    inline int mem_cmp(const void* _buf1, const void* _buf2, unsigned int n)
    {
        if (!!!n)
            return 0;

        while (--n && *(char*)_buf1 == *(char*)_buf2)
        {
            _buf1 = (char*)_buf1 + 1;
            _buf2 = (char*)_buf2 + 1;
        }

        return (int)(*((unsigned char*)_buf1) - *((unsigned char*)_buf2));
    }

    inline int mem_icmp(const void* _buf1, const void* _buf2, unsigned int n)
    {
        for (int _val1 = 0, _val2 = 0; n--;)
        {
            if (((_val1 = *(char*)_buf1) > 0x40) && (_val1 < 0x5b))
                _val1 |= 0x20;

            if (((_val2 = *(char*)_buf2) > 0x40) && (_val2 < 0x5b))
                _val2 |= 0x20;

            if (_val1 != _val2)
                return (_val1 - _val2);

            _buf1 = (char *)_buf1 + 1;
            _buf2 = (char *)_buf2 + 1;
        }

        return 0;
    }

    inline const wchar_t* wwmem_chr(const wchar_t* _ptr, int _wc, unsigned int n)
    {
        for (; 0 < n; ++_ptr, --n)
            if (*_ptr == _wc)
                return (_ptr);

        return (nullptr);
    }

    inline wchar_t* wmem_chr(wchar_t* _ptr, int _wc, unsigned int n)
    {
        return const_cast<wchar_t*>(wmem_chr(_ptr, _wc, n));
    }

    inline wchar_t* wmem_set(wchar_t* _ptr, wchar_t _val, unsigned int n)
    {
        for (wchar_t *wp = _ptr; 0 < n; ++wp, --n)
            *wp = _val;

        return (_ptr);
    }

    template<unsigned int _size> inline wchar_t* wmem_set(wchar_t(&_arr)[_size], wchar_t _val = 0)
    {
        return mem_set(_arr, _val, _size);
    }

    inline wchar_t* _wmem_cpy(wchar_t* _dst, const wchar_t* _src, unsigned int n)
    {
        for (wchar_t* start = _dst; 0 < n; --n)
            *start++ = *_src++;

        return (_dst);
    }

    inline wchar_t* _wmem_cpy(wchar_t* _dst, const wchar_t* _src, int _wc, unsigned int n)
    {
        while (n && (*_dst++ = *_src++) != _wc)
            --n;

        return 0 < n ? _dst : nullptr;
    }

    inline wchar_t* wmem_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n)
    {
        if (!!!(_dst && _src))
            return nullptr;

        return _wmem_cpy(_dst, _src, (n < _size ? n : _size));
    }

    inline wchar_t* wmem_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src, int _wc, unsigned int n)
    {
        if (!!!(_dst && _src))
            return _dst;

        return _wmem_cpy(_dst, _src, _wc, (n < _size ? n : _size));
    }

    template<unsigned int _size> inline wchar_t* wmem_cpy(wchar_t(&_dst)[_size], const wchar_t* _src, unsigned int n)
    {
        return wmem_cpy(_dst, _size, _src, n);
    }

    template<unsigned int _size> inline wchar_t* wmem_cpy(wchar_t(&_dst)[_size], const wchar_t* _src, int _wc, unsigned int n)
    {
        return wmem_cpy(_dst, _size, _src, _wc, n);
    }

    inline wchar_t* wmem_move(wchar_t* _dst, const wchar_t* _src, unsigned int n)
    {
        wchar_t* _start = _dst;

        if (_dst <= _src || _dst >= (_src + n))
            while (n--)
                *_dst++ = *_src++;
        else
            for (_dst += (n - 1), _src += (n - 1); n--; )
                *_dst-- = *_src--;

        return (_start);
    }

    inline wchar_t* wmem_move(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n)
    {
        if (!!!(_dst && _src && _size >= n))
            return _dst;

        return wmem_move(_dst, _src, n);
    }

    inline int wmem_cmp(const wchar_t* _buf1, const wchar_t* _buf2, unsigned int n)
    {
        for (; 0 < n; ++_buf1, ++_buf2, --n)
            if (*_buf1 != *_buf2)
                return ((*_buf1 < *_buf2) ? (-1) : (+1));

        return 0;
    }

    inline int wmem_icmp(const wchar_t* _buf1, const wchar_t* _buf2, unsigned int n)
    {
        const int _inv = L'a' - L'A';

        for (int _val1 = 0, _val2 = 0; n-- && (*_buf1 == *_buf2); ++_buf1, ++_buf2)
        {
            if (((_val1 = *_buf1) >= L'A') && (_val1 <= L'Z'))
                _val1 += _inv;

            if (((_val2 = *_buf2) >= L'A') && (_val2 <= L'Z'))
                _val2 += _inv;

            if (_val1 != _val2)
                return (_val1 - _val2);
        }

        return 0;
    }

}

#endif
