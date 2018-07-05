
#define CH(x, y, z)     (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z)    (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define EP0(x)  (_rotate_right(x, 0x02) ^ _rotate_right(x, 0x0d) ^ _rotate_right(x, 0x16))
#define EP1(x)  (_rotate_right(x, 0x06) ^ _rotate_right(x, 0x0b) ^ _rotate_right(x, 0x19))
#define SIG0(x) (_rotate_right(x, 0x07) ^ _rotate_right(x, 0x12) ^ ((x) >> 0x03))
#define SIG1(x) (_rotate_right(x, 0x11) ^ _rotate_right(x, 0x13) ^ ((x) >> 0x0a))

static constexpr unsigned int _key[64]{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static inline void _sha256_transform(unsigned int(&_state)[8], const unsigned char* _str)
{
    unsigned int a, b, c, d, e, f, g, h, t1, t2, m[64];

    m[0x00] = _make_uint(_str[0x03], _str[0x02], _str[0x01], _str[0x00]);
    m[0x01] = _make_uint(_str[0x07], _str[0x06], _str[0x05], _str[0x04]);
    m[0x02] = _make_uint(_str[0x0b], _str[0x0a], _str[0x09], _str[0x08]);
    m[0x03] = _make_uint(_str[0x0f], _str[0x0e], _str[0x0d], _str[0x0c]);
    m[0x04] = _make_uint(_str[0x13], _str[0x12], _str[0x11], _str[0x10]);
    m[0x05] = _make_uint(_str[0x17], _str[0x16], _str[0x15], _str[0x14]);
    m[0x06] = _make_uint(_str[0x1b], _str[0x1a], _str[0x19], _str[0x18]);
    m[0x07] = _make_uint(_str[0x1f], _str[0x1e], _str[0x1d], _str[0x1c]);
    m[0x08] = _make_uint(_str[0x23], _str[0x22], _str[0x21], _str[0x20]);
    m[0x09] = _make_uint(_str[0x27], _str[0x26], _str[0x25], _str[0x24]);
    m[0x0a] = _make_uint(_str[0x2b], _str[0x2a], _str[0x29], _str[0x28]);
    m[0x0b] = _make_uint(_str[0x2f], _str[0x2e], _str[0x2d], _str[0x2c]);
    m[0x0c] = _make_uint(_str[0x33], _str[0x32], _str[0x31], _str[0x30]);
    m[0x0d] = _make_uint(_str[0x37], _str[0x36], _str[0x35], _str[0x34]);
    m[0x0e] = _make_uint(_str[0x3b], _str[0x3a], _str[0x39], _str[0x38]);
    m[0x0f] = _make_uint(_str[0x3f], _str[0x3e], _str[0x3d], _str[0x3c]);

    for (unsigned int i = 16; i < 64; ++i)
    {
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
    }

    a = _state[0];
    b = _state[1];
    c = _state[2];
    d = _state[3];
    e = _state[4];
    f = _state[5];
    g = _state[6];
    h = _state[7];

    for (unsigned int i = 0; i < 64; ++i)
    {
        t1 = h + EP1(e) + CH(e, f, g) + _key[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
    _state[4] += e;
    _state[5] += f;
    _state[6] += g;
    _state[7] += h;
}

static inline void _sha256_final(unsigned int& _datalen, unsigned long long& _bitlen, unsigned int(&_state)[8], unsigned char(&_data)[64])
{
    _data[_datalen] = 0x80;

    if (_datalen < 56)
    {
        for (unsigned int i = _datalen + 1; i < 56; _data[i++] = 0x00);
    }
    else
    {
        for (unsigned int i = _datalen + 1; i < 64; _data[i++] = 0x00);

        _sha256_transform(_state, _data);

        for (unsigned int i = 0; i < 56; _data[i++] = 0x00);
    }

    _bitlen += (_datalen << 3);

    _data[63] = (_bitlen) & 0xff;
    _data[62] = (_bitlen >> 0x08) & 0xff;
    _data[61] = (_bitlen >> 0x10) & 0xff;
    _data[60] = (_bitlen >> 0x18) & 0xff;
    _data[59] = (_bitlen >> 0x20) & 0xff;
    _data[58] = (_bitlen >> 0x28) & 0xff;
    _data[57] = (_bitlen >> 0x30) & 0xff;
    _data[56] = (_bitlen >> 0x38) & 0xff;

    _sha256_transform(_state, _data);
}

void SHA256(unsigned char(&digest)[0x20], const unsigned char* in_str, unsigned int n)
{
    unsigned int state[8]{ 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
    unsigned int datalen{ 0 };
    unsigned long long bitlen{ 0 };
    unsigned char data[64]{ 0 };

    for (unsigned int i = 0; i < n; ++i)
    {
        data[datalen++] = in_str[i];

        if (0x40 == datalen)
        {
            _sha256_transform(state, data);

            bitlen += 512;
            datalen = 0;
        }
    }

    _sha256_final(datalen, bitlen, state, data);

    digest[0x00] = (state[0] >> 24) & 0xff;
    digest[0x04] = (state[1] >> 24) & 0xff;
    digest[0x08] = (state[2] >> 24) & 0xff;
    digest[0x0c] = (state[3] >> 24) & 0xff;
    digest[0x10] = (state[4] >> 24) & 0xff;
    digest[0x14] = (state[5] >> 24) & 0xff;
    digest[0x18] = (state[6] >> 24) & 0xff;
    digest[0x1c] = (state[7] >> 24) & 0xff;
    digest[0x01] = (state[0] >> 16) & 0xff;
    digest[0x05] = (state[1] >> 16) & 0xff;
    digest[0x09] = (state[2] >> 16) & 0xff;
    digest[0x0d] = (state[3] >> 16) & 0xff;
    digest[0x11] = (state[4] >> 16) & 0xff;
    digest[0x15] = (state[5] >> 16) & 0xff;
    digest[0x19] = (state[6] >> 16) & 0xff;
    digest[0x1d] = (state[7] >> 16) & 0xff;
    digest[0x02] = (state[0] >> 8) & 0xff;
    digest[0x06] = (state[1] >> 8) & 0xff;
    digest[0x0a] = (state[2] >> 8) & 0xff;
    digest[0x0e] = (state[3] >> 8) & 0xff;
    digest[0x12] = (state[4] >> 8) & 0xff;
    digest[0x16] = (state[5] >> 8) & 0xff;
    digest[0x1a] = (state[6] >> 8) & 0xff;
    digest[0x1e] = (state[7] >> 8) & 0xff;
    digest[0x03] = (state[0]) & 0xff;
    digest[0x07] = (state[1]) & 0xff;
    digest[0x0b] = (state[2]) & 0xff;
    digest[0x0f] = (state[3]) & 0xff;
    digest[0x13] = (state[4]) & 0xff;
    digest[0x17] = (state[5]) & 0xff;
    digest[0x1b] = (state[6]) & 0xff;
    digest[0x1f] = (state[7]) & 0xff;
}
