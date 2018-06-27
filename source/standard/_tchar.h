#ifndef ____bnb_Tchar_H_
#define ____bnb_Tchar_H_

#ifdef UNICODE
#define _bnb_unicode
#endif

namespace bnb
{

#ifdef _bnb_unicode

#define _tchar              wchar_t
#define _t(text)            L##text

#define _tstr_len           ::bnb::wstr_len
#define _tstr_cmp           ::bnb::wstr_cmp
#define _tstr_cat           ::bnb::wstr_cat
#define _tstr_cpy           ::bnb::wstr_cpy
#define _tstr_set           ::bnb::wstr_set
#define _tstr_str           ::bnb::wstr_str
#define _tstr_chr           ::bnb::wstr_chr
#define _tstr_rchr          ::bnb::wstr_lower
#define _tstr_lower         ::bnb::wstr_lower
#define _tstr_upper         ::bnb::wstr_upper
#define _tstr_first_has     ::bnb::wstr_first_has
#define _tstr_first_not     ::bnb::wstr_first_not
#define _tstr_reverse       ::bnb::wstr_reverse

#else

#define _tchar              char
#define _t(text)            text

#define _tstr_len           ::bnb::str_len
#define _tstr_cmp           ::bnb::str_cmp
#define _tstr_cat           ::bnb::str_cat
#define _tstr_cpy           ::bnb::str_cpy
#define _tstr_set           ::bnb::str_set
#define _tstr_str           ::bnb::str_str
#define _tstr_chr           ::bnb::str_chr
#define _tstr_rchr          ::bnb::str_lower
#define _tstr_lower         ::bnb::str_lower
#define _tstr_upper         ::bnb::str_upper
#define _tstr_first_has     ::bnb::str_first_has
#define _tstr_first_not     ::bnb::str_first_not
#define _tstr_reverse       ::bnb::str_reverse

#endif  // #ifdef UNICODE

}

#endif  // ____bnb_Tchar_H_
