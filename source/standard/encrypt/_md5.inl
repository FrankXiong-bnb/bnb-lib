
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (unsigned int)(ac); \
    (a) = _rotate_left ((a), (s)); \
    (a) += (b); \
    }
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (unsigned int)(ac); \
    (a) = _rotate_left ((a), (s)); \
    (a) += (b); \
    }
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (unsigned int)(ac); \
    (a) = _rotate_left ((a), (s)); \
    (a) += (b); \
    }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (unsigned int)(ac); \
    (a) = _rotate_left ((a), (s)); \
    (a) += (b); \
    }

static constexpr unsigned char _padding[64]{
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static inline void _md5_fransform(unsigned int(&_state)[4], const unsigned char* _block)
{
    unsigned int a = _state[0], b = _state[1], c = _state[2], d = _state[3];

    unsigned int x[16]{
        _make_uint(_block[0x00], _block[0x01], _block[0x02], _block[0x03]),
        _make_uint(_block[0x04], _block[0x05], _block[0x06], _block[0x07]),
        _make_uint(_block[0x08], _block[0x09], _block[0x0a], _block[0x0b]),
        _make_uint(_block[0x0c], _block[0x0d], _block[0x0e], _block[0x0f]),
        _make_uint(_block[0x10], _block[0x11], _block[0x12], _block[0x13]),
        _make_uint(_block[0x14], _block[0x15], _block[0x16], _block[0x17]),
        _make_uint(_block[0x18], _block[0x19], _block[0x1a], _block[0x1b]),
        _make_uint(_block[0x1c], _block[0x1d], _block[0x1e], _block[0x1f]),
        _make_uint(_block[0x20], _block[0x21], _block[0x22], _block[0x23]),
        _make_uint(_block[0x24], _block[0x25], _block[0x26], _block[0x27]),
        _make_uint(_block[0x28], _block[0x29], _block[0x2a], _block[0x2b]),
        _make_uint(_block[0x2c], _block[0x2d], _block[0x2e], _block[0x2f]),
        _make_uint(_block[0x30], _block[0x31], _block[0x32], _block[0x33]),
        _make_uint(_block[0x34], _block[0x35], _block[0x36], _block[0x37]),
        _make_uint(_block[0x38], _block[0x39], _block[0x3a], _block[0x3b]),
        _make_uint(_block[0x3c], _block[0x3d], _block[0x3e], _block[0x3f])
    };

    FF(a, b, c, d, x[0], 7, 0xd76aa478);     /* 1 */
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);     /* 2 */
    FF(c, d, a, b, x[2], 17, 0x242070db);     /* 3 */
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);     /* 4 */
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);     /* 5 */
    FF(d, a, b, c, x[5], 12, 0x4787c62a);     /* 6 */
    FF(c, d, a, b, x[6], 17, 0xa8304613);     /* 7 */
    FF(b, c, d, a, x[7], 22, 0xfd469501);     /* 8 */
    FF(a, b, c, d, x[8], 7, 0x698098d8);     /* 9 */
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);     /* 10 */
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);    /* 11 */
    FF(b, c, d, a, x[11], 22, 0x895cd7be);    /* 12 */
    FF(a, b, c, d, x[12], 7, 0x6b901122);    /* 13 */
    FF(d, a, b, c, x[13], 12, 0xfd987193);    /* 14 */
    FF(c, d, a, b, x[14], 17, 0xa679438e);    /* 15 */
    FF(b, c, d, a, x[15], 22, 0x49b40821);    /* 16 */

    GG(a, b, c, d, x[1], 5, 0xf61e2562);     /* 17 */
    GG(d, a, b, c, x[6], 9, 0xc040b340);     /* 18 */
    GG(c, d, a, b, x[11], 14, 0x265e5a51);    /* 19 */
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);     /* 20 */
    GG(a, b, c, d, x[5], 5, 0xd62f105d);     /* 21 */
    GG(d, a, b, c, x[10], 9, 0x2441453);     /* 22 */
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);    /* 23 */
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);     /* 24 */
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);     /* 25 */
    GG(d, a, b, c, x[14], 9, 0xc33707d6);    /* 26 */
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);     /* 27 */
    GG(b, c, d, a, x[8], 20, 0x455a14ed);     /* 28 */
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);    /* 29 */
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);     /* 30 */
    GG(c, d, a, b, x[7], 14, 0x676f02d9);     /* 31 */
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);    /* 32 */

    HH(a, b, c, d, x[5], 4, 0xfffa3942);     /* 33 */
    HH(d, a, b, c, x[8], 11, 0x8771f681);     /* 34 */
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);    /* 35 */
    HH(b, c, d, a, x[14], 23, 0xfde5380c);    /* 36 */
    HH(a, b, c, d, x[1], 4, 0xa4beea44);     /* 37 */
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);     /* 38 */
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);     /* 39 */
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);    /* 40 */
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);    /* 41 */
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);     /* 42 */
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);     /* 43 */
    HH(b, c, d, a, x[6], 23, 0x4881d05);      /* 44 */
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);     /* 45 */
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);    /* 46 */
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);    /* 47 */
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);     /* 48 */

    II(a, b, c, d, x[0], 6, 0xf4292244);     /* 49 */
    II(d, a, b, c, x[7], 10, 0x432aff97);     /* 50 */
    II(c, d, a, b, x[14], 15, 0xab9423a7);    /* 51 */
    II(b, c, d, a, x[5], 21, 0xfc93a039);     /* 52 */
    II(a, b, c, d, x[12], 6, 0x655b59c3);    /* 53 */
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);     /* 54 */
    II(c, d, a, b, x[10], 15, 0xffeff47d);    /* 55 */
    II(b, c, d, a, x[1], 21, 0x85845dd1);     /* 56 */
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);     /* 57 */
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);    /* 58 */
    II(c, d, a, b, x[6], 15, 0xa3014314);     /* 59 */
    II(b, c, d, a, x[13], 21, 0x4e0811a1);    /* 60 */
    II(a, b, c, d, x[4], 6, 0xf7537e82);     /* 61 */
    II(d, a, b, c, x[11], 10, 0xbd3af235);    /* 62 */
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);     /* 63 */
    II(b, c, d, a, x[9], 21, 0xeb86d391);     /* 64 */

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
}

static inline void _md5_update(const unsigned char *str, unsigned int n, unsigned int(&_state)[4], unsigned char(&_buffer)[64], unsigned int& _count0, unsigned int& _count1)
{
    unsigned int index = (unsigned int)((_count0 >> 3) & 0x3F);

    if ((_count0 += (n << 3)) < (n << 3))
        ++_count1;
    _count1 += (n >> 29);

    unsigned int i = 0;
    unsigned int partLen = 64 - index;

    if (n >= partLen)
    {
        _memcpy(_buffer + index, str, partLen);
        _md5_fransform(_state, _buffer);

        for (i = partLen; i + 63 < n; i += 64)
            _md5_fransform(_state, str + i);

        index = 0;
    }

    _memcpy(_buffer + index, str + i, n - i);
}

static inline void _md5_final(unsigned int(&_state)[4], unsigned char(&_buffer)[64], unsigned int& _count0, unsigned int& _count1)
{
    unsigned int index = (unsigned int)((_count0 >> 3) & 0x3f);
    unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);

    const unsigned char bits[8]{
        (unsigned char)(_count0 & 0xff),
        (unsigned char)((_count0 >> 8) & 0xff),
        (unsigned char)((_count0 >> 16) & 0xff),
        (unsigned char)((_count0 >> 24) & 0xff),
        (unsigned char)(_count1 & 0xff),
        (unsigned char)((_count1 >> 8) & 0xff),
        (unsigned char)((_count1 >> 16) & 0xff),
        (unsigned char)((_count1 >> 24) & 0xff)
    };

    _md5_update(_padding, padLen, _state, _buffer, _count0, _count1);

    _md5_update(bits, 8, _state, _buffer, _count0, _count1);
}

void MD5(unsigned char(&digest)[0x10], const unsigned char* str, unsigned int n)
{
    unsigned int _state[4]{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
    unsigned int _count0 = 0, _count1 = 0;
    unsigned char _buffer[64]{ 0 };

    _md5_update(str, n, _state, _buffer, _count0, _count1);
    _md5_final(_state, _buffer, _count0, _count1);

    digest[0x00] = (unsigned char)(_state[0] & 0xff);
    digest[0x04] = (unsigned char)(_state[1] & 0xff);
    digest[0x08] = (unsigned char)(_state[2] & 0xff);
    digest[0x0c] = (unsigned char)(_state[3] & 0xff);
    digest[0x01] = (unsigned char)((_state[0] >> 8) & 0xff);
    digest[0x05] = (unsigned char)((_state[1] >> 8) & 0xff);
    digest[0x09] = (unsigned char)((_state[2] >> 8) & 0xff);
    digest[0x0d] = (unsigned char)((_state[3] >> 8) & 0xff);
    digest[0x02] = (unsigned char)((_state[0] >> 16) & 0xff);
    digest[0x06] = (unsigned char)((_state[1] >> 16) & 0xff);
    digest[0x0a] = (unsigned char)((_state[2] >> 16) & 0xff);
    digest[0x0e] = (unsigned char)((_state[3] >> 16) & 0xff);
    digest[0x03] = (unsigned char)((_state[0] >> 24) & 0xff);
    digest[0x07] = (unsigned char)((_state[1] >> 24) & 0xff);
    digest[0x0b] = (unsigned char)((_state[2] >> 24) & 0xff);
    digest[0x0f] = (unsigned char)((_state[3] >> 24) & 0xff);
}
