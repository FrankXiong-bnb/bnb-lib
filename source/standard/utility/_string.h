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
     *  str_lower ���ַ���ת��ΪСд, str_upper ���ַ���ת��Ϊ��д��
     *
     *  ����:
     *      _str    - ָ��Ҫת�����ַ���
     *      n       - ָ��Ҫת�����ַ���
     *
     *  ����:
     *      ʵ��ת�����ַ��ĸ���
     */
    unsigned int str_lower(char* _str);
    unsigned int str_lower(char* _str, unsigned int n);
    unsigned int str_upper(char* _str);
    unsigned int str_upper(char* _str, unsigned int n);

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
    int str_cmp(const char* _str1, const char* _str2);
    int str_cmp(const char* _str1, const char* _str2, unsigned int n);
    int str_icmp(const char* _str1, const char* _str2);
    int str_icmp(const char* _str1, const char* _str2, unsigned int n);

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
    inline unsigned int str_len(const char* _str) { return t_str_len(_str); }
    inline unsigned int str_len(const char* _str, unsigned int maxsize) { return t_str_len(_str, maxsize); }

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
     *      _str_cat �汾����֤������Ϊ��
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
     *      _str_cpy �汾����֤������Ϊ��
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
     *      _str_set �汾����֤������Ϊ��
     *
     *      unsigned char ���ذ汾�� char �汾��Ϊһ����
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
    inline const char* str_chr(const char* _src, int _key) { return t_str_chr(_src, _key); }
    inline char* str_chr(char* _src, int _key) { return t_str_chr(_src, _key); }
    inline const char* str_rchr(const char* _src, int _key) { return t_str_rchr(_src, _key); }
    inline char* str_rchr(char* _src, int _key) { return t_str_rchr(_src, _key); }
    inline const char* str_str(const char* _src, const char* _key) { return t_str_str(_src, _key); }
    inline char* str_str(char* _src, const char* _key) { return t_str_str(_src, _key); }

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
     *	wstr_first_has�� wstr_first_not
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
