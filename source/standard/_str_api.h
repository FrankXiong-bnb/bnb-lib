//=============================================================================
// string operate
//  														2014-4 by Frank
//=============================================================================
#ifndef ____bnb_String_Api_H_
#define ____bnb_String_Api_H_

namespace bnb
{

/*
 *	str_lower, str_upper
 *
 *  str_lower 将字符串转换为小写, str_upper 将字符串转换为大写。
 *
 *  参数:
 *      _str    - 指定要转换的字符串
 *      n       - 指定要转换的字符数
 *
 *  返回:
 *      实际转换的字符的个数
 */
_overload_version(1) _size_t __bnbcall str_lower( _in_out char* _str );
_overload_version(2) _size_t __bnbcall str_lower( _in_out char* _str , _in _size_t n );
_overload_version(1) _size_t __bnbcall str_upper( _in_out char* _str );
_overload_version(2) _size_t __bnbcall str_upper( _in_out char* _str , _in _size_t n );

/*
 *	str_cmp, str_icmp
 *
 *  比较两个字符串，str_cmp 区分大小写，str_icmp 不区分大小写。
 *
 *  参数：
 *      _str1   - 指定第一个要比较的字符串
 *      _str2   - 指定第二个要比较的字符串
 *      n       - 指定要比较的字符数    
 *
 *  返回：
 *      返回 _str1 和 _str2 第一个不相同的字符对应的ansi码的差值，如果2个字符串相同则返回0。
 */
_overload_version(1) _result_t __bnbcall str_cmp( _in const char* _str1, _in const char* _str2 );
_overload_version(2) _result_t __bnbcall str_cmp( _in const char* _str1, _in const char* _str2, _in _size_t n );
_overload_version(1) _result_t __bnbcall str_icmp( _in const char* _str1, _in const char* _str2 );
_overload_version(2) _result_t __bnbcall str_icmp( _in const char* _str1, _in const char* _str2, _in _size_t n );

/*
 *	str_len
 *
 *  计算字符串的长度，不包括终止符。
 *
 *  参数：
 *      _str    - 指定要计算的字符串
 *      maxsize - 指定最大可以计算的长度
 *
 *  返回：
 *      _str 的长度。
 */
_overload_version(1) _size_t __bnbcall str_len( _in const char* _str );
_overload_version(2) _size_t __bnbcall str_len( _in const char* _str, _in _size_t maxsize );

/*
 *	str_cat
 *
 *  连接两个字符串
 *
 *  参数：
 *  重载版本1、2：
 *      _dst    - 指定目的字符串地址
 *      _size   - 指定目的字符串大小
 *      _src    - 指定要连接的字符串
 *      n       - 指定最大连接的字符数
 *  重载版本3、4：
 *      _dst    - 指定目的字符串数组名
 *      _size   - 模板数组的大小
 *
 *  返回：
 *      连接后字符串的长度
 *
 *  备注：
 *      str_cat 函数是安全的，将检查参数的有效性，并且保证目的字符串不会溢出。
 *      如果连接将产生大于 _size 长度的字符串，那么函数将会丢弃超过 _size 的部分，并在末尾添加'\0'。
 *      如果连接后的字符串小于 _size，则剩余部分用'\0'填充。
 *      重载的模板版本必须传递数组，而不是指针。
 *      _implicit_declare(_str_cat) 隐式声明版本不保证上述行为。
 */
_overload_version(1) _size_t __bnbcall str_cat( _out char* _dst, _in _size_t _size, _in const char* _src);
_overload_version(2) _size_t __bnbcall str_cat( _out char* _dst, _in _size_t _size, _in const char* _src, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall str_cat( _out char (&_dst)[_size], _in const char* _src);
_overload_version(4) template<_size_t _size> _size_t __bnbcall str_cat( _out char (&_dst)[_size], _in const char* _src, _in _size_t n );
_return_type(char*) __bnbcall _implicit_declare(_str_cat) _argument_list( _out char* _dst, _in const char* _src );
_return_type(char*) __bnbcall _implicit_declare(_str_cat) _argument_list( _out char* _dst, _in const char* _src, _in _size_t n );


/*
 *	str_cpy
 *
 *  拷贝字符串
 *
 *  参数：
 *  重载版本1、2：
 *      _dst    - 指定目的字符串地址
 *      _size   - 指定目的字符串大小
 *      _src    - 指定源字符串地址
 *      n       - 指定最大拷贝的字符数
 *  重载版本3、4：
 *      _dst    - 指定目的字符串数组名
 *      _size   - 模板数组的大小
 *
 *  返回：
 *      实际拷贝的字符数，不包含终止符。
 *
 *  备注：
 *      str_cpy 函数是安全的，将检查参数的有效性，并且保证目的字符串不会溢出。
 *      如果源字符串长度大于 _size ，那么函数将会丢弃超过 _size 的部分，并在末尾添加'\0'。
 *      如果源字符串长度小于 _size，则剩余部分用'\0'填充。
 *      重载的模板版本必须传递数组，而不是指针。
 *      _implicit_declare(_str_cpy) 隐式声明版本不保证上述行为。
 */
_overload_version(1) _size_t __bnbcall str_cpy( _out char* _dst, _in _size_t _size, _in const char* _src );
_overload_version(2) _size_t __bnbcall str_cpy( _out char* _dst, _in _size_t _size, _in const char* _src, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall str_cpy( _out char (&_dst)[_size], _in const char* _src );
_overload_version(4) template<_size_t _size> _size_t __bnbcall str_cpy( _out char (&_dst)[_size], _in const char* _src, _in _size_t n );
_return_type(char*) __bnbcall _implicit_declare(_str_cpy) _argument_list( _out char* _dst, _in const char* _src );
_return_type(char*) __bnbcall _implicit_declare(_str_cpy) _argument_list( _out char* _dst, _in const char* _src, _in _size_t n );

/*
 *	str_set
 *
 *  设置字符串为指定值
 *
 *  参数：
 *  重载版本1、2：
 *      _dst    - 指定目的字符串地址
 *      _size   - 指定目的字符串大小
 *      _val    - 指定要设置的值
 *      n       - 指定最大设置的字符数
 *  重载版本3、4：
 *      _dst    - 指定目的字符串数组名
 *      _size   - 模板数组的大小
 *
 *  返回：
 *      实际设置的字符数，不包含终止符。
 *
 *  备注：
 *      str_set 函数是安全的，将检查参数的有效性，并且保证目的字符串不会溢出。
 *      函数将设置目的字符串的每个字符的值为 _val，直到遇到 '\0'，多余的位置用'\0'填充。
 *      _implicit_declare(str_set) 隐式声明版本不保证上述行为。
 *  
 *      uchar 重载版本和 char 行为一样。
 */
_overload_version(1) _size_t __bnbcall str_set( _in_out char* _str, _in _size_t _size, _in int _val);
_overload_version(2) _size_t __bnbcall str_set( _in_out char* _str, _in _size_t _size, _in int _val, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall str_set( _in_out char (&_str)[_size], _in int _val);
_overload_version(4) template<_size_t _size> _size_t __bnbcall str_set( _in_out char (&_str)[_size], _in int _val, _in _size_t n );
_return_type(char*) __bnbcall _implicit_declare(_str_set) _argument_list( _in_out char* _str, _in int _val );
_return_type(char*) __bnbcall _implicit_declare(_str_set) _argument_list( _in_out char* _str, _in int _val, _in _size_t n );

_return_type(_size_t) __bnbcall _implicit_declare(str_set) _argument_list( _in_out uchar* _str, _in _size_t _size, _in uint _val)
{ return str_set((char*)_str, _size, (int)_val); }
_return_type(_size_t) __bnbcall _implicit_declare(str_set) _argument_list( _in_out uchar* _str, _in _size_t _size, _in uint _val, _in _size_t n )
{ return str_set((char*)_str, _size, (int)_val, n); }
template<_size_t _size> _return_type(_size_t) __bnbcall _implicit_declare(str_set) _argument_list( _in_out uchar (&_str)[_size], _in uint _val)
{ return str_set((char*)_str, _size, (int)_val); }
template<_size_t _size> _return_type(_size_t) __bnbcall _implicit_declare(str_set) _argument_list( _in_out uchar (&_str)[_size], _in uint _val, _in _size_t n )
{ return str_set((char*)_str, _size, (int)_val, n); }
_return_type(uchar*) __bnbcall _implicit_declare(_str_set) _argument_list( _in_out uchar* _str, _in uint _val )
{ return (uchar*)_str_set((char*)_str, (int)_val); }
_return_type(uchar*) __bnbcall _implicit_declare(_str_set) _argument_list( _in_out uchar* _str, _in uint _val, _in _size_t n )
{ return (uchar*)_str_set((char*)_str, (int)_val, n); }

/*
 *	str_chr, str_rchr, str_str
 *
 *  字符串查找
 *
 *  参数：
 *      _src    - 指定源字符串
 *      _key    - 指定要查找的内容
 *
 *  返回：
 *      返回要查找的内容完全匹配的位置，如果没有找到，返回 nullptr。
 *
 *  备注：
 *      str_chr 和 str_rchr 查找特定值，前者返回第一次出现的位置，后者返回最后一次出现的位置。
 *      str_str 查找特定字符串第一次出现的位置。
 */
_overload_version(1) const char* __bnbcall str_chr( _in const char* _src, _in int _key );
_overload_version(2) char* __bnbcall str_chr( _in char* _src, _in int _key );
_overload_version(1) const char* __bnbcall str_rchr( _in const char* _src, _in int _key );
_overload_version(2) char* __bnbcall str_rchr( _in char* _src, _in int _key );
_overload_version(1) const char* __bnbcall str_str( _in const char* _src, _in const char* _key );
_overload_version(2) char* __bnbcall str_str( _in char* _src, _in const char* _key );

/*
 *	str_first_has， str_first_not
 *
 *  校验字符串是否包含有特定字符集
 *
 *  参数：
 *      _dst    - 指定目标字符串
 *      _src    - 指定源字符串
 *
 *  返回：
 *      str_first_has 返回 _src 中包含的字符第一次在 _dst 中出现的位置。如果所有字符都没有在 _dst 中出现，返回 nullptr。
 *      str_first_not 返回 _src 中包含的字符第一次没有在 _dst 中出现的位置。如果所有字符都在 _dst 中出现，返回 nullptr。
 *
 *  备注：
 *      str_first_has 和 str_first_not 都不考虑终止符'\0'。
 *      隐式声明版本返回下标，如果没有找到符合要求的位置，则返回 '\0' 的位置。
 */
_overload_version(1) const char* __bnbcall str_first_has( _in const char* _dst, _in const char* _src );
_overload_version(1) const char* __bnbcall str_first_not( _in const char* _dst, _in const char* _src );
_overload_version(2) char* __bnbcall str_first_has( _in char* _dst, _in const char* _src );
_overload_version(2) char* __bnbcall str_first_not( _in char* _dst, _in const char* _src );
_return_type(_size_t) __bnbcall _implicit_declare(_str_first_has) _argument_list( _in const char* _dst, _in const char* _src );
_return_type(_size_t) __bnbcall _implicit_declare(_str_first_not) _argument_list( _in const char* _dst, _in const char* _src );
_return_type(_size_t) __bnbcall _implicit_declare(_str_map) _argument_list( _out uchar (&_map)[32], _in const char* _src );

/*
 *	str_reverse
 *
 *  反转字符串
 *
 *  参数：
 *      _str    - 指定待反转的字符串
 *      n       - 指定最大反转的字符数
 *
 *  返回：
 *      源字符串地址。
 *
 */
_overload_version(1) char* __bnbcall str_reverse( _in_out char* _str );
_overload_version(2) char* __bnbcall str_reverse( _in_out char* _str, _in _size_t n );


#ifndef _declare_inside_name
#define _declare_inside_name(_name)   _piece_together_name(str, _name)

#include "../standard/_str_case.inl"
#include "../standard/_str_cmp.inl"

#define _implicit_inside_name(_name)  _piece_together_name(_str, _name)

#include "../standard/_str_spn.inl"

#define _char_t char

#include "../standard/_tstr_set.inl"
#include "../standard/_tstr_cat.inl"
#include "../standard/_tstr_cpy.inl"

#undef _implicit_inside_name

#include "../standard/_tstr_len.inl"
#include "../standard/_tstr_find.inl"
#include "../standard/_tstr_reverse.inl"

#undef _char_t

#undef _declare_inside_name
#endif  // #ifndef _declare_inside_name


/*
 *	wstr_lower
 *
 */
_overload_version(1) _size_t __bnbcall wstr_lower( _in_out wchar* _str );
_overload_version(2) _size_t __bnbcall wstr_lower( _in_out wchar* _str , _in _size_t n );
_overload_version(1) _size_t __bnbcall wstr_upper( _in_out wchar* _str );
_overload_version(2) _size_t __bnbcall wstr_upper( _in_out wchar* _str , _in _size_t n );

/*
 *	wstr_cmp, wstr_icmp
 */
_overload_version(1) _result_t __bnbcall wstr_cmp( _in const wchar* _str1, _in const wchar* _str2 );
_overload_version(2) _result_t __bnbcall wstr_cmp( _in const wchar* _str1, _in const wchar* _str2, _in _size_t n );
_overload_version(1) _result_t __bnbcall wstr_icmp( _in const wchar* _str1, _in const wchar* _str2 );
_overload_version(2) _result_t __bnbcall wstr_icmp( _in const wchar* _str1, _in const wchar* _str2, _in _size_t n );

/*
 *	wstr_len
 */
_overload_version(1) _size_t __bnbcall wstr_len( _in const wchar* _str );
_overload_version(2) _size_t __bnbcall wstr_len( _in const wchar* _str, _in _size_t maxsize );

/*
 *	wstr_cat
 */
_overload_version(1) _size_t __bnbcall wstr_cat( _out wchar_t* _dst, _in _size_t _size, _in const wchar_t* _src);
_overload_version(2) _size_t __bnbcall wstr_cat( _out wchar_t* _dst, _in _size_t _size, _in const wchar_t* _src, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall wstr_cat( _out wchar_t (&_dst)[_size], _in const wchar_t* _src);
_overload_version(4) template<_size_t _size> _size_t __bnbcall wstr_cat( _out wchar_t (&_dst)[_size], _in const wchar_t* _src, _in _size_t n );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_cat) _argument_list( _out wchar* _dst, _in const wchar* _src );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_cat) _argument_list( _out wchar* _dst, _in const wchar* _src, _in _size_t n );


/*
 *	wstr_cpy
 */
_overload_version(1) _size_t __bnbcall wstr_cpy( _out wchar* _dst, _in _size_t _size, _in const wchar* _src );
_overload_version(2) _size_t __bnbcall wstr_cpy( _out wchar* _dst, _in _size_t _size, _in const wchar* _src, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall wstr_cpy( _out wchar (&_dst)[_size], _in const wchar* _src );
_overload_version(4) template<_size_t _size> _size_t __bnbcall wstr_cpy( _out wchar (&_dst)[_size], _in const wchar* _src, _in _size_t n );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_cpy) _argument_list( _out wchar* _dst, _in const wchar* _src );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_cpy) _argument_list( _out wchar* _dst, _in const wchar* _src, _in _size_t n );

/*
 *	wstr_set
 */
_overload_version(1) _size_t __bnbcall wstr_set( _in_out wchar* _str, _in _size_t _size, _in int _val);
_overload_version(2) _size_t __bnbcall wstr_set( _in_out wchar* _str, _in _size_t _size, _in int _val, _in _size_t n );
_overload_version(3) template<_size_t _size> _size_t __bnbcall wstr_set( _in_out wchar (&_str)[_size], _in int _val);
_overload_version(4) template<_size_t _size> _size_t __bnbcall wstr_set( _in_out wchar (&_str)[_size], _in int _val, _in _size_t n );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_set) _argument_list( _in_out wchar* _str, _in int _val );
_return_type(wchar*) __bnbcall _implicit_declare(_wstr_set) _argument_list( _in_out wchar* _str, _in int _val, _in _size_t n );

/*
 *	wstr_chr, wstr_rchr, wstr_str
 */
_overload_version(1) const wchar* __bnbcall wstr_chr( _in const wchar* _src, _in int _key );
_overload_version(2) wchar* __bnbcall wstr_chr( _in wchar* _src, _in int _key );
_overload_version(1) const wchar* __bnbcall wstr_rchr( _in const wchar* _src, _in int _key );
_overload_version(2) wchar* __bnbcall wstr_rchr( _in wchar* _src, _in int _key );
_overload_version(1) const wchar* __bnbcall wstr_str( _in const wchar* _src, _in const wchar* _key );
_overload_version(2) wchar* __bnbcall wstr_str( _in wchar* _src, _in const wchar* _key );

/*
 *	wstr_first_has， wstr_first_not
 */
_overload_version(1) const wchar* __bnbcall wstr_first_has( _in const wchar* _dst, _in const wchar* _src );
_overload_version(1) const wchar* __bnbcall wstr_first_not( _in const wchar* _dst, _in const wchar* _src );
_overload_version(2) wchar* __bnbcall wstr_first_has( _in wchar* _dst, _in const wchar* _src );
_overload_version(2) wchar* __bnbcall wstr_first_not( _in wchar* _dst, _in const wchar* _src );

/*
 *	wstr_reverse
 */
_overload_version(1) wchar* __bnbcall wstr_reverse( _in_out wchar* _str );
_overload_version(2) wchar* __bnbcall wstr_reverse( _in_out wchar* _str, _in _size_t n );


#ifndef _declare_inside_name
#define _declare_inside_name(_name)   _piece_together_name(wstr, _name)

#include "../standard/_wstr_case.inl"
#include "../standard/_wstr_cmp.inl"
#include "../standard/_wstr_spn.inl"

#define _char_t wchar

#define _implicit_inside_name(_name)  _piece_together_name(_wstr, _name)
#include "../standard/_tstr_set.inl"
#include "../standard/_tstr_cat.inl"
#include "../standard/_tstr_cpy.inl"
#undef _implicit_inside_name

#include "../standard/_tstr_len.inl"
#include "../standard/_tstr_find.inl"
#include "../standard/_tstr_reverse.inl"

#undef _char_t

#undef _declare_inside_name
#endif  // #ifndef _declare_inside_name

}


#endif