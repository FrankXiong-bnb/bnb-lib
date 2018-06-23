#ifndef ____bnb_utility_h_
#define ____bnb_utility_h_

_bnb_space_in

bool is_digit(int _c);
bool is_alpha(int _c);
bool is_lower(int _c);
bool is_upper(int _c);
bool is_print(int _c);

double str_to_double(const char* _str);
long str_to_long(const char* _str);

_size_t long_to_str(long _val, char* _buf, int _base);
_size_t double_to_str(double _val, char* _buf, int _base);

double wstr_to_double(const chwr* _str);
long wstr_to_long(const chwr* _str);

_size_t long_to_wstr(long _val, chwr* _buf, int _base);
_size_t double_to_wstr(double _val, chwr* _buf, int _base);

unsigned long rand();
int rand(int left, int right);

_declare_inline void reversal(const char* str, unsigned int size, char* buf)
{
    for (unsigned int i=0; i<size; ++i ) buf[i] = str[size-i-1];

    buf[size] = 0;
}

_declare_inline bool plus(const char* digit1, unsigned int len1, const char* digit2, unsigned int len2, char* result)
{
    unsigned int max = (len1 > len2) ? len1 : len2;
    char* buf = new char[max + 1];

    bool k = false;

    for (unsigned int i=0; i<max; ++i)
    {
        char a = 0, b = 0;

        if (i<len1) a = digit1[len1-i-1] - '0';
        if (i<len2) b = digit2[len2-i-1] - '0';

        k = ((buf[i] = a + b + k) > 9);
        buf[i] = buf[i]%10 + '0';
    }

    buf[max] = '0' + k;
    reversal(buf, max+k, result);

    delete [] buf;

    return k;
}

_bnb_space_out

#endif