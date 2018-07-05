//=============================================================================
// Explanation:
// 		Define the class string with bnb.
//
// Date: 2014-3     Author: Frank
//=============================================================================
#ifndef ____bnb_String_Class_H_
#define ____bnb_String_Class_H_


namespace bnb
{

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
            = sizeof(_charT) <= 1 ? ((1 << ((sizeof(size_type) << 3) - 1)) - 2)
            : sizeof(_charT) <= 2 ? ((1 << ((sizeof(size_type) << 3) - 2)) - 2)
            : sizeof(_charT) <= 4 ? ((1 << ((sizeof(size_type) << 3) - 3)) - 2)
            : sizeof(_charT) <= 8 ? ((1 << ((sizeof(size_type) << 3) - 4)) - 2)
            : ((1 << (sizeof(size_type) << 2)) - 2)
        };

        static const pos_type end_pos = 1 << ((sizeof(pos_type) << 3) - 1);

    private:

        union {
            _charT  _arr[__buf_size];
            _charT* _ptr;
        }_data;

        size_type  _size;
        size_type  _capacity;

    public:

        ~base_string();
        base_string();
        base_string(const char_type* str);
        base_string(const string_type& str);
        base_string(char_type c, size_type n = 1);
        base_string(const char_type* str, size_type n);
        base_string(const string_type& str, pos_type pos, size_type n);

    public:

        string_type& operator  = (const string_type& str);
        string_type& operator  = (const char_type* str);
        string_type& operator  = (char_type c);
        string_type& operator += (const string_type& str);
        string_type& operator += (const char_type* str);
        string_type& operator += (char_type c);

        char_type& operator [] (pos_type index);
        const char_type& operator [] (pos_type index) const;

        void  Clear();
        bool  Swap(string_type& str);
        bool  IsEmpty() const;

        const string_type PartOf(pos_type pos, size_type n) const;
        const char_type*  string() const;

        size_type  Size() const;
        size_type  Capacity() const;
        size_type  MaxSize() const;
        size_type  Copy(char_type* str, size_type n, pos_type pos = 0) const;

        pos_type   Find(char_type c, pos_type pos = 0) const;
        pos_type   Find(const string_type& str, pos_type pos = 0) const;
        pos_type   Find(const char_type* str, pos_type pos = 0) const;
        pos_type   Find(const char_type* str, pos_type pos, size_type n) const;

        pos_type   FindLast(const string_type& str, pos_type pos = end_pos) const;
        pos_type   FindLast(char_type c, pos_type pos = end_pos) const;
        pos_type   FindLast(const char_type* str, pos_type pos = end_pos) const;
        pos_type   FindLast(const char_type* str, pos_type pos, size_type n) const;

        pos_type   FindFirstOf(const string_type& str, pos_type pos = end_pos) const;
        pos_type   FindFirstOf(const char_type* str, pos_type pos = end_pos) const;
        pos_type   FindFirstOf(const char_type* str, pos_type pos, size_type n) const;
        pos_type   FindLastOf(const string_type& str, pos_type pos = end_pos) const;
        pos_type   FindLastOf(const char_type* str, pos_type pos = end_pos) const;
        pos_type   FindLastOf(const char_type* str, pos_type pos, size_type n) const;

        pos_type   FindFirstNotOf(char_type c, pos_type pos = 0) const;
        pos_type   FindFirstNotOf(const string_type& str, pos_type pos = end_pos) const;
        pos_type   FindFirstNotOf(const char_type* str, pos_type pos = end_pos) const;
        pos_type   FindFirstNotOf(const char_type* str, pos_type pos, size_type n) const;
        pos_type   FindLastNotOf(char_type c, pos_type pos = 0) const;
        pos_type   FindLastNotOf(const string_type& str, pos_type pos = end_pos) const;
        pos_type   FindLastNotOf(const char_type* str, pos_type pos = end_pos) const;
        pos_type   FindLastNotOf(const char_type* str, pos_type pos, size_type n) const;

        int        Compare(const char_type* str, size_type n) const;
        int        Compare(const string_type& str, pos_type pos, size_type n) const;
        int        Compare(size_type n, pos_type pos, const char_type* str) const;
        int        Compare(size_type n, pos_type pos, const string_type& str, pos_type pos2 = 0) const;
        int        CompareNoCase(const char_type* str, size_type n) const;
        int        CompareNoCase(const string_type& str, pos_type pos, size_type n) const;
        int        CompareNoCase(size_type n, pos_type pos, const char_type* str) const;
        int        CompareNoCase(size_type n, pos_type pos, const string_type& str, pos_type pos2 = 0) const;

        bool       Append(char_type c, size_type n);
        bool       Append(const char_type* str, size_type n);
        bool       Append(const string_type& str, pos_type pos, size_type n);
        bool       Assign(char_type c, size_type n);
        bool       Assign(const char_type* str, size_type n);
        bool       Assign(const string_type& str, pos_type pos, size_type n);

        bool       Insert(pos_type pos, char_type c, size_type n = 1);
        bool       Insert(pos_type pos, const char_type* str);
        bool       Insert(pos_type pos, const char_type* str, size_type n);
        bool       Insert(pos_type pos, const string_type& str);
        bool       Insert(pos_type pos, const string_type& str, pos_type pos2, size_type n2);

        bool       Replace(pos_type pos, size_type n, char_type c, size_type m = 1);
        bool       Replace(pos_type pos, size_type n, const char_type* str);
        bool       Replace(pos_type pos, size_type n, const char_type* str, size_type m);
        bool       Replace(pos_type pos, size_type n, const string_type& str);
        bool       Replace(pos_type pos, size_type n, const string_type& str, pos_type pos2, size_type n2);
        size_type  Replace(char_type key, char_type aim);
        size_type  Replace(char_type key, const char_type* dst);
        size_type  Replace(const char_type* src, char_type aim);
        size_type  Replace(const char_type* src, const char_type* dst);

        bool       Erase(pos_type pos = 0, size_type n = end_pos);
        size_type  Delete(char_type key, pos_type pos = 0);
        size_type  Delete(const char_type* str, pos_type pos = 0);
        size_type  Delete(const string_type& str, pos_type pos = 0);

        friend void Swap(string_type& str1, string_type& str2);
        friend const string_type operator + (const string_type& str1, const string_type& str2);
        friend bool operator  < (const string_type& str1, const string_type& str2);
        friend bool operator  > (const string_type& str1, const string_type& str2);
        friend bool operator <= (const string_type& str1, const string_type& str2);
        friend bool operator >= (const string_type& str1, const string_type& str2);
        friend bool operator == (const string_type& str1, const string_type& str2);
        friend bool operator != (const string_type& str1, const string_type& str2);

    };  // class base_string

    using String    = base_string<char, trait_char<char>>;
    using WString   = base_string<wchar_t, trait_char<wchar_t>>;

}


#endif  // ____bnb_String_Class_H_
