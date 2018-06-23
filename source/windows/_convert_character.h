//=============================================================================
// convert character
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Convert_Character_H_
#define ____bnb_Convert_Character_H_

_bnb_space_in

_declare_inline
bool WideStringToMultiString(
      _out char* buf
    , _in _size_t size
    , _in const wchar_t* src
    , _in _size_t n = _TRUNCATE
    , _out _size_t* count = nullptr
    , _in const char* locale = "")
{
    if (nullptr == locale) return (0 == wcstombs_s(count, buf, size, src, n));

    _locale_t plocale = _create_locale(LC_CTYPE, locale);
    if (nullptr == plocale) return false;
    
    int err = _wcstombs_s_l(count, buf, size, src, n, plocale);
    _free_locale(plocale);

    return (0 == err);
}

template<_size_t size> _declare_inline
bool WideStringToMultiString(
      _out char (&buf)[size]
    , _in const wchar_t* src
    , _in _size_t n = _TRUNCATE
    , _out _size_t* count = nullptr
    , _in const char* locale = "")
{
    return WideStringToMultiString(buf, size, src, n, count, locale);
}

_declare_inline
bool MultiStringToWideString(
      _out wchar_t* buf
    , _in _size_t size
    , _in const char* src
    , _in _size_t n = _TRUNCATE
    , _out _size_t* count = nullptr
    , _in const char* locale = "")
{
    if (nullptr == locale) return (0 == mbstowcs_s(count, buf, size, src, n));

    _locale_t plocale = _create_locale(LC_CTYPE, locale);
    if (nullptr == plocale) return false;

    int err = _mbstowcs_s_l(count, buf, size, src, n, plocale);
    _free_locale(plocale);

    return (0 == err);
}

template<_size_t size> _declare_inline
bool MultiStringToWideString(
      _out wchar_t (&buf)[size]
    , _in const char* src
    , _in _size_t n = _TRUNCATE
    , _out _size_t* count = nullptr
    , _in const char* locale = "")
{
    return MultiStringToWideString(buf, size, src, n, count, locale);
}

_bnb_space_out

#endif