#ifndef ____bnb_Memory_H_
#define ____bnb_Memory_H_

namespace bnb
{

    const void* mem_chr(const void* _ptr, int _c, unsigned int n);
    void* mem_chr(void* _ptr, int _c, unsigned int n);

    void* mem_set(void* _ptr, int _val, unsigned int n);

    template<typename _Ty, unsigned int _size> inline _Ty* mem_set(_Ty(&_arr)[_size], const _Ty& _val = 0)
    {
        for (_index_t index = _size; index; _arr[--index] = _val);

        return (_arr);
    }

    void* _mem_cpy(void* _dst, const void* _src, unsigned int n);
    void* _mem_cpy(void* _dst, const void* _src, int _c, unsigned int n);
    void* mem_cpy(void* _dst, unsigned int _size, const void* _src, unsigned int n);
    void* mem_cpy(void* _dst, unsigned int _size, const void* _src, int _c, unsigned int n);

    template<typename _Ty, unsigned int _size> inline _Ty* mem_cpy(_Ty(&_dst)[_size], const void* _src, unsigned int n)
    {
        return static_cast<_Ty*>(mem_cpy(_dst, _size * sizeof(_Ty), _src, n));
    }

    template<typename _Ty, unsigned int _size> inline _Ty* mem_cpy(_Ty(&_dst)[_size], const void* _src, int _c, unsigned int n)
    {
        return static_cast<_Ty*>(mem_cpy(_dst, _size * sizeof(_Ty), _src, _c, n));
    }

    void* mem_move(void* _dst, const void* _src, unsigned int n);
    void* mem_move(void* _dst, unsigned int _size, const void* _src, unsigned int n);

    int mem_cmp(const void* _buf1, const void* _buf2, unsigned int n);
    int mem_icmp(const void* _buf1, const void* _buf2, unsigned int n);

    const wchar_t* wwmem_chr(const wchar_t* _ptr, int _wc, unsigned int n);
    wchar_t* wmem_chr(wchar_t* _ptr, int _wc, unsigned int n);

    wchar_t* wmem_set(wchar_t* _ptr, wchar_t _val, unsigned int n);

    template<unsigned int _size> inline wchar_t* wmem_set(wchar_t(&_arr)[_size], wchar_t _val = 0)
    {
        return mem_set(_arr, _val, _size);
    }

    wchar_t* _wmem_cpy(wchar_t* _dst, const wchar_t* _src, unsigned int n);
    wchar_t* _wmem_cpy(wchar_t* _dst, const wchar_t* _src, int _wc, unsigned int n);
    wchar_t* wmem_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n);
    wchar_t* wmem_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src, int _wc, unsigned int n);

    template<unsigned int _size> inline wchar_t* wmem_cpy(wchar_t(&_dst)[_size], const wchar_t* _src, unsigned int n)
    {
        return wmem_cpy(_dst, _size, _src, n);
    }

    template<unsigned int _size> inline wchar_t* wmem_cpy(wchar_t(&_dst)[_size], const wchar_t* _src, int _wc, unsigned int n)
    {
        return wmem_cpy(_dst, _size, _src, _wc, n);
    }

    wchar_t* wmem_move(wchar_t* _dst, const wchar_t* _src, unsigned int n);
    wchar_t* wmem_move(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n);

    int wmem_cmp(const wchar_t* _buf1, const wchar_t* _buf2, unsigned int n);
    int wmem_icmp(const wchar_t* _buf1, const wchar_t* _buf2, unsigned int n);

}

#endif
