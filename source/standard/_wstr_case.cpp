
namespace bnb
{

inline unsigned int wstr_lower(wchar_t* _wstr)
{
    unsigned int count = 0;

    for (; *_wstr; ++_wstr)
    {
        if (L'A' <= *_wstr && *_wstr <= L'Z')
        {
            *_wstr += (L'a' - L'A');
            ++count;
        }
    }

    return count;
}

inline unsigned int wstr_lower(wchar_t* _wstr, unsigned int n)
{
    unsigned int count = 0;

    for (; (n-- && *_wstr); ++_wstr)
    {
        if (L'A' <= *_wstr && *_wstr <= L'Z')
        {
            *_wstr += (L'a' - L'A');
            ++count;
        }
    }

    return count;
}

inline unsigned int wstr_upper(wchar_t* _wstr)
{
    unsigned int count = 0;

    for (; *_wstr; ++_wstr)
    {
        if (L'a' <= *_wstr && *_wstr <= L'z')
        {
            *_wstr -= (L'a' - L'A');
            ++count;
        }
    }

    return count;
}

inline unsigned int wstr_upper(wchar_t* _wstr, unsigned int n)
{
    unsigned int count = 0;

    for (; (n-- && *_wstr); ++_wstr)
    {
        if (L'a' <= *_wstr && *_wstr <= L'z')
        {
            *_wstr -= (L'a' - L'A');
            ++count;
        }
    }

    return count;
}

}
