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
 *  str_lower ���ַ���ת��ΪСд, str_upper ���ַ���ת��Ϊ��д��
 *
 *  ����:
 *      _str    - ָ��Ҫת�����ַ���
 *      n       - ָ��Ҫת�����ַ���
 *
 *  ����:
 *      ʵ��ת�����ַ��ĸ���
 */
_overload_version(1) _size_t __bnbcall str_lower( _in_out char* _str );
_overload_version(2) _size_t __bnbcall str_lower( _in_out char* _str , _in _size_t n );
_overload_version(1) _size_t __bnbcall str_upper( _in_out char* _str );
_overload_version(2) _size_t __bnbcall str_upper( _in_out char* _str , _in _size_t n );

/*
 *	str_cmp, str_icmp
 *
 *  �Ƚ������ַ�����str_cmp ���ִ�Сд��str_icmp �����ִ�Сд��
 *
 *  ������
 *      _str1   - ָ����һ��Ҫ�Ƚϵ��ַ���
 *      _str2   - ָ���ڶ���Ҫ�Ƚϵ��ַ���
 *      n       - ָ��Ҫ�Ƚϵ��ַ���    
 *
 *  ���أ�
 *      ���� _str1 �� _str2 ��һ������ͬ���ַ���Ӧ��ansi��Ĳ�ֵ�����2���ַ�����ͬ�򷵻�0��
 */
_overload_version(1) _result_t __bnbcall str_cmp( _in const char* _str1, _in const char* _str2 );
_overload_version(2) _result_t __bnbcall str_cmp( _in const char* _str1, _in const char* _str2, _in _size_t n );
_overload_version(1) _result_t __bnbcall str_icmp( _in const char* _str1, _in const char* _str2 );
_overload_version(2) _result_t __bnbcall str_icmp( _in const char* _str1, _in const char* _str2, _in _size_t n );

/*
 *	str_len
 *
 *  �����ַ����ĳ��ȣ���������ֹ����
 *
 *  ������
 *      _str    - ָ��Ҫ������ַ���
 *      maxsize - ָ�������Լ���ĳ���
 *
 *  ���أ�
 *      _str �ĳ��ȡ�
 */
_overload_version(1) _size_t __bnbcall str_len( _in const char* _str );
_overload_version(2) _size_t __bnbcall str_len( _in const char* _str, _in _size_t maxsize );

/*
 *	str_cat
 *
 *  ���������ַ���
 *
 *  ������
 *  ���ذ汾1��2��
 *      _dst    - ָ��Ŀ���ַ�����ַ
 *      _size   - ָ��Ŀ���ַ�����С
 *      _src    - ָ��Ҫ���ӵ��ַ���
 *      n       - ָ��������ӵ��ַ���
 *  ���ذ汾3��4��
 *      _dst    - ָ��Ŀ���ַ���������
 *      _size   - ģ������Ĵ�С
 *
 *  ���أ�
 *      ���Ӻ��ַ����ĳ���
 *
 *  ��ע��
 *      str_cat �����ǰ�ȫ�ģ�������������Ч�ԣ����ұ�֤Ŀ���ַ������������
 *      ������ӽ��������� _size ���ȵ��ַ�������ô�������ᶪ������ _size �Ĳ��֣�����ĩβ���'\0'��
 *      ������Ӻ���ַ���С�� _size����ʣ�ಿ����'\0'��䡣
 *      ���ص�ģ��汾���봫�����飬������ָ�롣
 *      _implicit_declare(_str_cat) ��ʽ�����汾����֤������Ϊ��
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
 *  �����ַ���
 *
 *  ������
 *  ���ذ汾1��2��
 *      _dst    - ָ��Ŀ���ַ�����ַ
 *      _size   - ָ��Ŀ���ַ�����С
 *      _src    - ָ��Դ�ַ�����ַ
 *      n       - ָ����󿽱����ַ���
 *  ���ذ汾3��4��
 *      _dst    - ָ��Ŀ���ַ���������
 *      _size   - ģ������Ĵ�С
 *
 *  ���أ�
 *      ʵ�ʿ������ַ�������������ֹ����
 *
 *  ��ע��
 *      str_cpy �����ǰ�ȫ�ģ�������������Ч�ԣ����ұ�֤Ŀ���ַ������������
 *      ���Դ�ַ������ȴ��� _size ����ô�������ᶪ������ _size �Ĳ��֣�����ĩβ���'\0'��
 *      ���Դ�ַ�������С�� _size����ʣ�ಿ����'\0'��䡣
 *      ���ص�ģ��汾���봫�����飬������ָ�롣
 *      _implicit_declare(_str_cpy) ��ʽ�����汾����֤������Ϊ��
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
 *  �����ַ���Ϊָ��ֵ
 *
 *  ������
 *  ���ذ汾1��2��
 *      _dst    - ָ��Ŀ���ַ�����ַ
 *      _size   - ָ��Ŀ���ַ�����С
 *      _val    - ָ��Ҫ���õ�ֵ
 *      n       - ָ��������õ��ַ���
 *  ���ذ汾3��4��
 *      _dst    - ָ��Ŀ���ַ���������
 *      _size   - ģ������Ĵ�С
 *
 *  ���أ�
 *      ʵ�����õ��ַ�������������ֹ����
 *
 *  ��ע��
 *      str_set �����ǰ�ȫ�ģ�������������Ч�ԣ����ұ�֤Ŀ���ַ������������
 *      ����������Ŀ���ַ�����ÿ���ַ���ֵΪ _val��ֱ������ '\0'�������λ����'\0'��䡣
 *      _implicit_declare(str_set) ��ʽ�����汾����֤������Ϊ��
 *  
 *      uchar ���ذ汾�� char ��Ϊһ����
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
 *  �ַ�������
 *
 *  ������
 *      _src    - ָ��Դ�ַ���
 *      _key    - ָ��Ҫ���ҵ�����
 *
 *  ���أ�
 *      ����Ҫ���ҵ�������ȫƥ���λ�ã����û���ҵ������� nullptr��
 *
 *  ��ע��
 *      str_chr �� str_rchr �����ض�ֵ��ǰ�߷��ص�һ�γ��ֵ�λ�ã����߷������һ�γ��ֵ�λ�á�
 *      str_str �����ض��ַ�����һ�γ��ֵ�λ�á�
 */
_overload_version(1) const char* __bnbcall str_chr( _in const char* _src, _in int _key );
_overload_version(2) char* __bnbcall str_chr( _in char* _src, _in int _key );
_overload_version(1) const char* __bnbcall str_rchr( _in const char* _src, _in int _key );
_overload_version(2) char* __bnbcall str_rchr( _in char* _src, _in int _key );
_overload_version(1) const char* __bnbcall str_str( _in const char* _src, _in const char* _key );
_overload_version(2) char* __bnbcall str_str( _in char* _src, _in const char* _key );

/*
 *	str_first_has�� str_first_not
 *
 *  У���ַ����Ƿ�������ض��ַ���
 *
 *  ������
 *      _dst    - ָ��Ŀ���ַ���
 *      _src    - ָ��Դ�ַ���
 *
 *  ���أ�
 *      str_first_has ���� _src �а������ַ���һ���� _dst �г��ֵ�λ�á���������ַ���û���� _dst �г��֣����� nullptr��
 *      str_first_not ���� _src �а������ַ���һ��û���� _dst �г��ֵ�λ�á���������ַ����� _dst �г��֣����� nullptr��
 *
 *  ��ע��
 *      str_first_has �� str_first_not ����������ֹ��'\0'��
 *      ��ʽ�����汾�����±꣬���û���ҵ�����Ҫ���λ�ã��򷵻� '\0' ��λ�á�
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
 *  ��ת�ַ���
 *
 *  ������
 *      _str    - ָ������ת���ַ���
 *      n       - ָ�����ת���ַ���
 *
 *  ���أ�
 *      Դ�ַ�����ַ��
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
 *	wstr_first_has�� wstr_first_not
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