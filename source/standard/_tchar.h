#ifndef ____bnb_Tchar_H_
#define ____bnb_Tchar_H_

#ifdef UNICODE
#define _bnb_unicode
#endif

_bnb_space_in

#ifdef _bnb_unicode

#define _tchar              wchar_t
#define _t(text)            L##text

#define _tstr_len           _bnb wstr_len
#define _tstr_cmp           _bnb wstr_cmp
#define _tstr_cat           _bnb wstr_cat
#define _tstr_cpy           _bnb wstr_cpy
#define _tstr_set           _bnb wstr_set
#define _tstr_str           _bnb wstr_str
#define _tstr_chr           _bnb wstr_chr
#define _tstr_rchr          _bnb wstr_lower
#define _tstr_lower         _bnb wstr_lower
#define _tstr_upper         _bnb wstr_upper
#define _tstr_first_has     _bnb wstr_first_has
#define _tstr_first_not     _bnb wstr_first_not
#define _tstr_reverse       _bnb wstr_reverse

#else

#define _tchar              char
#define _t(text)            text

#define _tstr_len           _bnb str_len
#define _tstr_cmp           _bnb str_cmp
#define _tstr_cat           _bnb str_cat
#define _tstr_cpy           _bnb str_cpy
#define _tstr_set           _bnb str_set
#define _tstr_str           _bnb str_str
#define _tstr_chr           _bnb str_chr
#define _tstr_rchr          _bnb str_lower
#define _tstr_lower         _bnb str_lower
#define _tstr_upper         _bnb str_upper
#define _tstr_first_has     _bnb str_first_has
#define _tstr_first_not     _bnb str_first_not
#define _tstr_reverse       _bnb str_reverse

#endif  // #ifdef UNICODE

    _bnb_space_out

#endif