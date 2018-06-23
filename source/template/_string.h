//=============================================================================
// Explanation:
// 		Define the class string with bnb.
//
// Date: 2014-3     Author: Frank
//=============================================================================
#ifndef ____bnb_class_string_h_
#define ____bnb_class_string_h_


_bnb_space_in

template<typename _charT, typename _traitT>
class base_string
{
public:

    typedef _charT  char_type;
    typedef _charT* pchar_type;
    typedef _charT& rchar_type;

    typedef unsigned int pos_type;
    typedef unsigned int size_type;

    typedef base_string<_charT>  string_type;

    enum {
        __buf_size = sizeof(_charT) <= 1 ? 0x20 : sizeof(_charT) <= 2 ? 0x10 : 0x08,

        __max_size
        = sizeof(_charT) <= 1 ? ((1<<((sizeof(size_type)<<3) - 1)) - 2)
        : sizeof(_charT) <= 2 ? ((1<<((sizeof(size_type)<<3) - 2)) - 2)
        : sizeof(_charT) <= 4 ? ((1<<((sizeof(size_type)<<3) - 3)) - 2)
        : sizeof(_charT) <= 8 ? ((1<<((sizeof(size_type)<<3) - 4)) - 2)
        : ((1<<(sizeof(size_type)<<2)) - 2)
    };

    _declare_static _declare_const pos_type end_pos = 1<<((sizeof(pos_type)<<3)-1);

private:

    union{
        _charT  _arr[__buf_size];
        _charT* _ptr;
    }_data;

    size_type  _size;
    size_type  _capacity;

public:

    ~base_string();
    base_string();
    base_string(_in const char_type* str);
    base_string(_in const string_type& str);
    base_string(_in char_type c, _in size_type n = 1);
    base_string(_in const char_type* str, _in size_type n);
    base_string(_in const string_type& str, _in pos_type pos, _in size_type n);

public:

    string_type& operator  = (_in const string_type& str);
    string_type& operator  = (_in const char_type* str);
    string_type& operator  = (_in char_type c);
    string_type& operator += (_in const string_type& str);
    string_type& operator += (_in const char_type* str);
    string_type& operator += (_in char_type c);

    char_type& operator [] (_in pos_type index);
    const char_type& operator [] (_in pos_type index) const;

    void  Clear();
    bool  Swap(_in_out string_type& str);
    bool  IsEmpty() const;

    const string_type PartOf(_in pos_type pos, _in size_type n) const;
    const char_type*  string() const;

    size_type  Size() const;
    size_type  Capacity() const;
    size_type  MaxSize() const;
    size_type  Copy(_out char_type* str, _in size_type n, _in pos_type pos = 0) const;

    pos_type   Find(_in char_type c, _in pos_type pos = 0) const;
    pos_type   Find(_in const string_type& str, _in pos_type pos = 0) const;
    pos_type   Find(_in const char_type* str, _in pos_type pos = 0) const;
    pos_type   Find(_in const char_type* str, _in pos_type pos, _in size_type n) const;

    pos_type   rFind(_in const string_type& str, _in pos_type pos = end_pos) const;
    pos_type   rFind(_in char_type c, _in pos_type pos = end_pos) const;
    pos_type   rFind(_in const char_type* str, _in pos_type pos = end_pos) const;
    pos_type   rFind(_in const char_type* str, _in pos_type pos, _in size_type n) const;

    pos_type   FindFirstOf(_in const string_type& str, _in pos_type pos = end_pos) const;
    pos_type   FindFirstOf(_in const char_type* str, _in pos_type pos = end_pos) const;
    pos_type   FindFirstOf(_in const char_type* str, _in pos_type pos, _in size_type n) const;
    pos_type   FindLastOf(_in const string_type& str, _in pos_type pos = end_pos) const;
    pos_type   FindLastOf(_in const char_type* str, _in pos_type pos = end_pos) const;
    pos_type   FindLastOf(_in const char_type* str, _in pos_type pos, _in size_type n) const;

    pos_type   FindFirstNotOf(_in char_type c, _in pos_type pos = 0) const;
    pos_type   FindFirstNotOf(_in const string_type& str, _in pos_type pos = end_pos) const;
    pos_type   FindFirstNotOf(_in const char_type* str, _in pos_type pos = end_pos) const;
    pos_type   FindFirstNotOf(_in const char_type* str, _in pos_type pos, _in size_type n) const;
    pos_type   FindLastNotOf(_in char_type c, _in pos_type pos = 0) const;
    pos_type   FindLastNotOf(_in const string_type& str, _in pos_type pos = end_pos) const;
    pos_type   FindLastNotOf(_in const char_type* str, _in pos_type pos = end_pos) const;
    pos_type   FindLastNotOf(_in const char_type* str, _in pos_type pos, _in size_type n) const;

    _result_t  Compare(_in const char_type* str, _in size_type n) const;
    _result_t  Compare(_in const string_type& str, _in pos_type pos, _in size_type n) const;
    _result_t  Compare(_in size_type n, _in pos_type pos, _in const char_type* str) const;
    _result_t  Compare(_in size_type n, _in pos_type pos, _in const string_type& str, _in pos_type pos2 = 0) const;
    _result_t  CompareNoCase(_in const char_type* str, _in size_type n) const;
    _result_t  CompareNoCase(_in const string_type& str, _in pos_type pos, _in size_type n) const;
    _result_t  CompareNoCase(_in size_type n, _in pos_type pos, _in const char_type* str) const;
    _result_t  CompareNoCase(_in size_type n, _in pos_type pos, _in const string_type& str, _in pos_type pos2 = 0) const;

    bool       Append(_in char_type c, _in size_type n);
    bool       Append(_in const char_type* str, _in size_type n);
    bool       Append(_in const string_type& str, _in pos_type pos, _in size_type n);
    bool       Assign(_in char_type c, _in size_type n);
    bool       Assign(_in const char_type* str, _in size_type n);
    bool       Assign(_in const string_type& str, _in pos_type pos, _in size_type n);

    bool       Insert(_in pos_type pos, _in char_type c, _in size_type n=1);
    bool       Insert(_in pos_type pos, _in const char_type* str);
    bool       Insert(_in pos_type pos, _in const char_type* str, _in size_type n);
    bool       Insert(_in pos_type pos, _in const string_type& str);
    bool       Insert(_in pos_type pos, _in const string_type& str, _in pos_type pos2, _in size_type n2);

    bool       Replace(_in pos_type pos, _in size_type n, _in char_type c, _in size_type m = 1);
    bool       Replace(_in pos_type pos, _in size_type n, _in const char_type* str);
    bool       Replace(_in pos_type pos, _in size_type n, _in const char_type* str, _in size_type m);
    bool       Replace(_in pos_type pos, _in size_type n, _in const string_type& str);
    bool       Replace(_in pos_type pos, _in size_type n, _in const string_type& str, _in pos_type pos2, _in size_type n2);
    size_type  Replace(_in char_type key, _in char_type aim);
    size_type  Replace(_in char_type key, _in const char_type* dst);
    size_type  Replace(_in const char_type* src, _in char_type aim);
    size_type  Replace(_in const char_type* src, _in const char_type* dst);

    bool       Erase(_in pos_type pos = 0, _in size_type n = end_pos);
    size_type  Delete(_in char_type key, _in pos_type pos = 0);
    size_type  Delete(_in const char_type* str, _in pos_type pos = 0);
    size_type  Delete(_in const string_type& str, _in pos_type pos = 0);

    _declare_friend void Swap(_in_out string_type& str1, _in_out string_type& str2);
    _declare_friend const string_type operator + (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator  < (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator  > (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator <= (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator >= (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator == (_in const string_type& str1, _in const string_type& str2);
    _declare_friend bool operator != (_in const string_type& str1, _in const string_type& str2);

};  // class base_string


#ifdef _bnb_string

typedef base_string<char, trait_char<char>>         string;
typedef base_string<wchar_t, trait_char<wchar_t>>   wstring;

typedef bnb::string     bnbstr;
typedef bnb::wstring    bnbwstr;

#endif


_bnb_space_out


#endif
