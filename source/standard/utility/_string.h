//=============================================================================
// string operate
//  														2014-4 by Frank
//=============================================================================
#ifndef ____bnb_String_Api_H_
#define ____bnb_String_Api_H_

namespace bnb
{

#include "_tstr_set.inl"
#include "_tstr_cat.inl"
#include "_tstr_cpy.inl"
#include "_tstr_len.inl"
#include "_tstr_find.inl"
#include "_tstr_reverse.inl"

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
    unsigned int str_lower(char* _str);
    unsigned int str_lower(char* _str, unsigned int n);
    unsigned int str_upper(char* _str);
    unsigned int str_upper(char* _str, unsigned int n);

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
    int str_cmp(const char* _str1, const char* _str2);
    int str_cmp(const char* _str1, const char* _str2, unsigned int n);
    int str_icmp(const char* _str1, const char* _str2);
    int str_icmp(const char* _str1, const char* _str2, unsigned int n);

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
    inline unsigned int str_len(const char* _str) { return t_str_len(_str); }
    inline unsigned int str_len(const char* _str, unsigned int maxsize) { return t_str_len(_str, maxsize); }

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
     *      _str_cat 版本不保证上述行为。
     */
    inline char* _str_cat(char* _dst, const char* _src) { return _t_str_cat(_dst, _src); }
    inline char* _str_cat(char* _dst, const char* _src, unsigned int n) { return _t_str_cat(_dst, _src, n); }
    inline unsigned int str_cat(char* _dst, unsigned int _size, const char* _src) { return t_str_cat(_dst, _size, _src); }
    inline unsigned int str_cat(char* _dst, unsigned int _size, const char* _src, unsigned int n) { return t_str_cat(_dst, _size, _src, n); }
    template<unsigned int _size> inline unsigned int str_cat(char(&_dst)[_size], const char* _src) { return t_str_cat(_dst, _src); }
    template<unsigned int _size> inline unsigned int str_cat(char(&_dst)[_size], const char* _src, unsigned int n) { return t_str_cat(_dst, _src, n); }

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
     *      _str_cpy 版本不保证上述行为。
     */
    inline char* _str_cpy(char* _dst, const char* _src) { return _t_str_cpy(_dst, _src); }
    inline char* _str_cpy(char* _dst, const char* _src, unsigned int n) { return _t_str_cpy(_dst, _src, n); }
    inline unsigned int str_cpy(char* _dst, unsigned int _size, const char* _src) { return t_str_cpy(_dst, _size, _src); }
    inline unsigned int str_cpy(char* _dst, unsigned int _size, const char* _src, unsigned int n) { return t_str_cpy(_dst, _size, _src, n); }
    template<unsigned int _size> inline unsigned int str_cpy(char(&_dst)[_size], const char* _src) { return t_str_cpy(_dst, _src); }
    template<unsigned int _size> inline unsigned int str_cpy(char(&_dst)[_size], const char* _src, unsigned int n) { return t_str_cpy(_dst, _src, n); }

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
     *      _str_set 版本不保证上述行为。
     *
     *      unsigned char 重载版本和 char 版本行为一样。
     */
    inline char* _str_set(char* _str, int _val) { return _t_str_set(_str, _val); }
    inline char* _str_set(char* _str, int _val, unsigned int n) { return _t_str_set(_str, _val, n); }
    inline unsigned int str_set(char* _str, unsigned int _size, int _val) { return t_str_set(_str, _size, _val); }
    inline unsigned int str_set(char* _str, unsigned int _size, int _val, unsigned int n) { return t_str_set(_str, _size, _val, n); }
    template<unsigned int _size> inline unsigned int str_set(char(&_str)[_size], int _val) { return t_str_set(_str, _val); }
    template<unsigned int _size> inline unsigned int str_set(char(&_str)[_size], int _val, unsigned int n) { return t_str_set(_str, _val, n); }

    inline unsigned char* _str_set(unsigned char* _str, unsigned int _val) { return (unsigned char*)_str_set((char*)_str, (int)_val); }
    inline unsigned char* _str_set(unsigned char* _str, unsigned int _val, unsigned int n) { return (unsigned char*)_str_set((char*)_str, (int)_val, n); }
    inline unsigned int str_set(unsigned char* _str, unsigned int _size, unsigned int _val) { return str_set((char*)_str, _size, (int)_val); }
    inline unsigned int str_set(unsigned char* _str, unsigned int _size, unsigned int _val, unsigned int n) { return str_set((char*)_str, _size, (int)_val, n); }
    template<unsigned int _size> inline unsigned int str_set(unsigned char(&_str)[_size], unsigned int _val) { return str_set((char*)_str, _size, (int)_val); }
    template<unsigned int _size> inline unsigned int str_set(unsigned char(&_str)[_size], unsigned int _val, unsigned int n) { return str_set((char*)_str, _size, (int)_val, n); }

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
    inline const char* str_chr(const char* _src, int _key) { return t_str_chr(_src, _key); }
    inline char* str_chr(char* _src, int _key) { return t_str_chr(_src, _key); }
    inline const char* str_rchr(const char* _src, int _key) { return t_str_rchr(_src, _key); }
    inline char* str_rchr(char* _src, int _key) { return t_str_rchr(_src, _key); }
    inline const char* str_str(const char* _src, const char* _key) { return t_str_str(_src, _key); }
    inline char* str_str(char* _src, const char* _key) { return t_str_str(_src, _key); }

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
    const char* str_first_has(const char* _dst, const char* _src);
    const char* str_first_not(const char* _dst, const char* _src);
    char* str_first_has(char* _dst, const char* _src);
    char* str_first_not(char* _dst, const char* _src);
    unsigned int _str_first_has(const char* _dst, const char* _src);
    unsigned int _str_first_not(const char* _dst, const char* _src);
    // _return_type(_size_t) _implicit_declare(_str_map) _argument_list( uchar (&_map)[32], const char* _src );

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
    inline char* str_reverse(char* _str) { return t_str_reverse(_str); }
    inline char* str_reverse(char* _str, unsigned int n) { return t_str_reverse(_str, n); }

    /*
     *	wstr_lower, wstr_upper
     */
    unsigned int wstr_lower(wchar_t* _str);
    unsigned int wstr_lower(wchar_t* _str, unsigned int n);
    unsigned int wstr_upper(wchar_t* _str);
    unsigned int wstr_upper(wchar_t* _str, unsigned int n);

    /*
     *	wstr_cmp, wstr_icmp
     */
    int wstr_cmp(const wchar_t* _str1, const wchar_t* _str2);
    int wstr_cmp(const wchar_t* _str1, const wchar_t* _str2, unsigned int n);
    int wstr_icmp(const wchar_t* _str1, const wchar_t* _str2);
    int wstr_icmp(const wchar_t* _str1, const wchar_t* _str2, unsigned int n);

    /*
     *	wstr_len
     */
    inline unsigned int wstr_len(const wchar_t* _str) { return t_str_len(_str); }
    inline unsigned int wstr_len(const wchar_t* _str, unsigned int maxsize) { return t_str_len(_str, maxsize); }

    /*
     *	wstr_cat
     */
    inline wchar_t* _wstr_cat(wchar_t* _dst, const wchar_t* _src) { return _t_str_cat(_dst, _src); }
    inline wchar_t* _wstr_cat(wchar_t* _dst, const wchar_t* _src, unsigned int n) { return _t_str_cat(_dst, _src, n); }
    inline unsigned int wstr_cat(wchar_t* _dst, unsigned int _size, const wchar_t* _src) { return t_str_cat(_dst, _size, _src); }
    inline unsigned int wstr_cat(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n) { return t_str_cat(_dst, _size, _src, n); }
    template<unsigned int _size> inline unsigned int wstr_cat(wchar_t(&_dst)[_size], const wchar_t* _src) { return t_str_cat(_dst, _src); }
    template<unsigned int _size> inline unsigned int wstr_cat(wchar_t(&_dst)[_size], const wchar_t* _src, unsigned int n) { return t_str_cat(_dst, _src, n); }

    /*
     *	wstr_cpy
     */
    inline wchar_t* _wstr_cpy(wchar_t* _dst, const wchar_t* _src) { return _t_str_cpy(_dst, _src); }
    inline wchar_t* _wstr_cpy(wchar_t* _dst, const wchar_t* _src, unsigned int n) { return _t_str_cpy(_dst, _src, n); }
    inline unsigned int wstr_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src) { return t_str_cpy(_dst, _size, _src); }
    inline unsigned int wstr_cpy(wchar_t* _dst, unsigned int _size, const wchar_t* _src, unsigned int n) { return t_str_cpy(_dst, _size, _src, n); }
    template<unsigned int _size> inline unsigned int wstr_cpy(wchar_t(&_dst)[_size], const wchar_t* _src) { return t_str_cpy(_dst, _src); }
    template<unsigned int _size> inline unsigned int wstr_cpy(wchar_t(&_dst)[_size], const wchar_t* _src, unsigned int n) { return t_str_cpy(_dst, _src, n); }

    /*
     *	wstr_set
     */
    inline wchar_t* _wstr_set(wchar_t* _str, int _val) { return _t_str_set(_str, _val); }
    inline wchar_t* _wstr_set(wchar_t* _str, int _val, unsigned int n) { return _t_str_set(_str, _val, n); }
    inline unsigned int wstr_set(wchar_t* _str, unsigned int _size, int _val) { return t_str_set(_str, _size, _val); }
    inline unsigned int wstr_set(wchar_t* _str, unsigned int _size, int _val, unsigned int n) { return t_str_set(_str, _size, _val, n); }
    template<unsigned int _size> inline unsigned int wstr_set(wchar_t(&_str)[_size], int _val) { return t_str_set(_str, _val); }
    template<unsigned int _size> inline unsigned int wstr_set(wchar_t(&_str)[_size], int _val, unsigned int n) { return t_str_set(_str, _val, n); }

    /*
     *	wstr_chr, wstr_rchr, wstr_str
     */
    inline const wchar_t* wstr_chr(const wchar_t* _src, int _key) { return t_str_chr(_src, _key); }
    inline wchar_t* wstr_chr(wchar_t* _src, int _key) { return t_str_chr(_src, _key); }
    inline const wchar_t* wstr_rchr(const wchar_t* _src, int _key) { return t_str_rchr(_src, _key); }
    inline wchar_t* wstr_rchr(wchar_t* _src, int _key) { return t_str_rchr(_src, _key); }
    inline const wchar_t* wstr_str(const wchar_t* _src, const wchar_t* _key) { return t_str_str(_src, _key); }
    inline wchar_t* wstr_str(wchar_t* _src, const wchar_t* _key) { return t_str_str(_src, _key); }

    /*
     *	wstr_first_has， wstr_first_not
     */
    const wchar_t* wstr_first_has(const wchar_t* _dst, const wchar_t* _src);
    const wchar_t* wstr_first_not(const wchar_t* _dst, const wchar_t* _src);
    wchar_t* wstr_first_has(wchar_t* _dst, const wchar_t* _src);
    wchar_t* wstr_first_not(wchar_t* _dst, const wchar_t* _src);

    /*
     *	wstr_reverse
     */
    inline wchar_t* wstr_reverse(wchar_t* _str) { return t_str_reverse(_str); }
    inline wchar_t* wstr_reverse(wchar_t* _str, unsigned int n) { return t_str_reverse(_str, n); }

}

#endif
