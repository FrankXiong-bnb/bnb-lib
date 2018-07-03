namespace bnb
{

    static constexpr unsigned char _character[16]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

    void _to_hex_str(unsigned char* dst, const unsigned char* src, unsigned int n)
    {
        for (unsigned int i = 0; i < n; ++i)
        {
            dst[i << 1] = _character[src[i] >> 4];
            dst[(i << 1) + 1] = _character[src[i] & 0x0f];
        }
    }

    static inline void _memcpy(unsigned char* dst, const unsigned char*         src, unsigned int    n)
    {
        while (n--)
            *dst++ = *src++;
    }
    /*
    static inline void _memset(unsigned char* dst, int             value, unsigned int    n)
    {
        while (n--)
            *dst++ = value;
    }
    */
    static inline unsigned int _make_uint(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
    {
        return (a | (b << 8) | (c << 16) | (d << 24));
    }

    static inline unsigned int _rotate_left(unsigned int x, unsigned int n)
    {
        return (x << n) | (x >> (32 - n));
    }

    static inline unsigned int _rotate_right(unsigned int x, unsigned int n)
    {
        return (x >> n) | (x << (32 - n));
    }


#include "_sha256.inl"
#include "_md5.inl"

}
