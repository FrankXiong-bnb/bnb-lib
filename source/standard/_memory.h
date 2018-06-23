#ifndef ____bnb_Memory_H_
#define ____bnb_Memory_H_

_bnb_space_in

_overload_version(1) const void* __bnbcall mem_chr( _in const void* _ptr, _in int _c, _in _size_t n );
_overload_version(2) void* __bnbcall mem_chr( _in void* _ptr, _in int _c, _in _size_t n );

_overload_version(1) template<typename _Ty, _size_t _size> _Ty* __bnbcall mem_set( _out _Ty (&_arr)[_size], _in int _val = 0 );
_overload_version(2) void* __bnbcall mem_set( _out void* _ptr, _in int _val, _in _size_t n );

_return_type(void*) __bnbcall _implicit_declare(_mem_cpy) _argument_list( _out void* _dst, _in const void* _src, _in _size_t n );
_return_type(void*) __bnbcall _implicit_declare(_mem_cpy) _argument_list( _out void* _dst, _in const void* _src, _in int _c, _in _size_t n );
_overload_version(1) template<typename _Ty, _size_t _size> _Ty* __bnbcall mem_cpy( _out _Ty (&_dst)[_size], _in const void* _src, _in _size_t n );
_overload_version(2) template<typename _Ty, _size_t _size> _Ty* __bnbcall mem_cpy( _out _Ty (&_dst)[_size], _in const void* _src, _in int _c, _in _size_t n );
_overload_version(3) void* __bnbcall mem_cpy( _out void* _dst, _in _size_t _size, _in const void* _src, _in _size_t n );
_overload_version(4) void* __bnbcall mem_cpy( _out void* _dst, _in _size_t _size, _in const void* _src, _in int _c, _in _size_t n );

_overload_version(1) void* __bnbcall mem_move( _out void* _dst, _in const void* _src, _in _size_t n );
_overload_version(2) void* __bnbcall mem_move( _out void* _dst, _in _size_t size, _in const void* _src, _in _size_t n );

_overload_version(1) _result_t __bnbcall mem_cmp( _in const void* _buf1, _in const void* _buf2, _in _size_t n );
_overload_version(2) _result_t __bnbcall mem_icmp( _in const void* _buf1, _in const void* _buf2, _in _size_t n );


_overload_version(1) const wchar* __bnbcall wwmem_chr( _in const wchar* _ptr, _in int _wc, _in _size_t n );
_overload_version(2) wchar* __bnbcall wmem_chr( _in wchar* _ptr, _in int _wc, _in _size_t n );

_overload_version(1) template<_size_t _size> wchar* __bnbcall wmem_set( _out wchar_t (&_arr)[_size], _in wchar_t _val = 0 );
_overload_version(2) wchar* __bnbcall wmem_set( _out wchar_t* _ptr, _in wchar_t _val, _in _size_t n );

_return_type(wchar*) __bnbcall _implicit_declare(_wmem_cpy) _argument_list( _out wchar* _dst, _in const wchar* _src, _in _size_t n );
_return_type(wchar*) __bnbcall _implicit_declare(_wmem_cpy) _argument_list( _out wchar* _dst, _in const wchar* _src, _in int _wc, _in _size_t n );
_overload_version(1) template<_size_t _size> wchar* __bnbcall wmem_cpy( _out wchar_t (&_dst)[_size], _in const wchar_t* _src, _in _size_t n );
_overload_version(2) template<_size_t _size> wchar* __bnbcall wmem_cpy( _out wchar_t (&_dst)[_size], _in const wchar_t* _src, _in int _wc, _in _size_t n );
_overload_version(3) wchar* __bnbcall wmem_cpy( _out wchar_t* _dst, _in _size_t _size, _in const wchar_t* _src, _in _size_t n );
_overload_version(4) wchar* __bnbcall wmem_cpy( _out wchar_t* _dst, _in _size_t _size, _in const wchar_t* _src, _in int _wc, _in _size_t n );

_overload_version(1) wchar* __bnbcall wmem_move( _out wchar* _dst, _in const wchar* _src, _in _size_t n );
_overload_version(2) wchar* __bnbcall wmem_move( _out wchar* _dst, _in _size_t size, _in const wchar* _src, _in _size_t n );

_overload_version(1) _result_t __bnbcall wmem_cmp( _in const wchar* _buf1, _in const wchar* _buf2, _in _size_t n );
_overload_version(2) _result_t __bnbcall wmem_icmp( _in const wchar* _buf1, _in const wchar* _buf2, _in _size_t n );


#ifndef _declare_inside_name
#define _declare_inside_name(_name)     _bnb_declare(_name)

#define _implicit_inside_name(_name)    _bnb_declare(_name)

#include "../standard/_memory.inl"

#undef _implicit_inside_name

#undef _declare_inside_name
#endif  // #ifndef _declare_inside_name

_bnb_space_out


#endif