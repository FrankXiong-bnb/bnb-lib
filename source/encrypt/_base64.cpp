#include "_base64.h"

namespace bnb
{
    const unsigned char _base64_alphabet_ex[64]{
        '7', 'X', 'w', 'e', '8', 'r', 't', 'u', 'g', '0', 'P', 'A', '2', 's', 'k', '5',
        'd', '-', '4', 'h', 'J', 'z', 'C', '3', 'v', 'y', '6', 'b', 'n', 'm', '1', 'i',
        'F', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'o', 'p', 'a', 'S', 'D', '*', 'G',
        'H', 'j', 'K', 'L', 'Z', 'x', 'c', 'V', 'q', 'N', 'M', 'l', 'B', '9', 'f', 'O'
    };

    static const unsigned char _base64_alphabet[64]{
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
        0x2b, 0x2f
    };

    static const unsigned char _base64_mapping[256]{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f,
        0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
        0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    unsigned int Base64Encrypt(unsigned char* dst, const unsigned char* src, unsigned int n)
    {
        unsigned int off = n % 3;
        unsigned int count = (n / 3) << 2;
        if (0 < off)
        {
            count += 4;
            n -= off;
        }

        if (nullptr != dst && nullptr != src)
        {
            for (unsigned int i = 0; i < n; i += 3, src += 3, dst += 4)
            {
                dst[0] = _base64_alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _base64_alphabet[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
                dst[2] = _base64_alphabet[((src[1] & 0x0f) << 2) | ((src[2] & 0xc0) >> 6)];
                dst[3] = _base64_alphabet[src[2] & 0x3f];
            }

            switch (off)
            {
            case 1:
                dst[0] = _base64_alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _base64_alphabet[(src[0] & 0x03) << 4];
                dst[2] = 0x3d;
                dst[3] = 0x3d;
                break;
            case 2:
                dst[0] = _base64_alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _base64_alphabet[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
                dst[2] = _base64_alphabet[(src[1] & 0x0f) << 2];
                dst[3] = 0x3d;
                break;
            default:
                break;
            }
        }
        
        return count;
    }
    
    unsigned int Base64Decrypt(unsigned char* dst, const unsigned char* src, unsigned int n)
    {
        if (0 < n % 4 || 0 == n)
            return 0;

        unsigned int count = (n >> 2) * 3;
        if (0x3d == src[n - 1])
            --count;
        if (0x3d == src[n - 2])
            --count;

        if (nullptr != dst && nullptr != src)
        {
            n -= 4;
            for (unsigned int i = 0; i < n; i += 4, src += 4, dst += 3)
            {
                dst[0] = ((_base64_mapping[src[0]] & 0x3f) << 2) | ((_base64_mapping[src[1]] & 0x30) >> 4);
                dst[1] = ((_base64_mapping[src[1]] & 0x0f) << 4) | ((_base64_mapping[src[2]] & 0x3c) >> 2);
                dst[2] = ((_base64_mapping[src[2]] & 0x03) << 6) | (_base64_mapping[src[3]] & 0x3f);
            }

            if (0x3d == src[3])
            {
                if (0x3d == src[2])
                {
                    dst[0] = ((_base64_mapping[src[0]] & 0x3f) << 2) | ((_base64_mapping[src[1]] & 0x30) >> 4);
                }
                else
                {
                    dst[0] = ((_base64_mapping[src[0]] & 0x3f) << 2) | ((_base64_mapping[src[1]] & 0x30) >> 4);
                    dst[1] = ((_base64_mapping[src[1]] & 0x0f) << 4) | ((_base64_mapping[src[2]] & 0x3c) >> 2);
                }
            }
            else
            {
                dst[0] = ((_base64_mapping[src[0]] & 0x3f) << 2) | ((_base64_mapping[src[1]] & 0x30) >> 4);
                dst[1] = ((_base64_mapping[src[1]] & 0x0f) << 4) | ((_base64_mapping[src[2]] & 0x3c) >> 2);
                dst[2] = ((_base64_mapping[src[2]] & 0x03) << 6) | (_base64_mapping[src[3]] & 0x3f);
            }
        }

        return count;
    }
    

    EncoderBase64::EncoderBase64(const unsigned char(&_map)[64])
    {
        if (CheckAlphabet(_map))
            _appoint(_map);
        else
            _appoint(_base64_alphabet_ex);
    }

    unsigned int EncoderBase64::Encrypt(unsigned char * dst, const unsigned char * src, unsigned int n) const
    {
        unsigned int off = n % 3;
        unsigned int count = (n / 3) << 2;
        if (0 < off)
        {
            count += (off + 1);
            n -= off;
        }

        if (nullptr != dst && nullptr != src)
        {
            for (unsigned int i = 0; i < n; i += 3, src += 3, dst += 4)
            {
                dst[0] = _alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _alphabet[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
                dst[2] = _alphabet[((src[1] & 0x0f) << 2) | ((src[2] & 0xc0) >> 6)];
                dst[3] = _alphabet[src[2] & 0x3f];
            }

            switch (off)
            {
            case 1:
                dst[0] = _alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _alphabet[(src[0] & 0x03) << 4];
                break;
            case 2:
                dst[0] = _alphabet[(src[0] & 0xfc) >> 2];
                dst[1] = _alphabet[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
                dst[2] = _alphabet[(src[1] & 0x0f) << 2];
                break;
            default:
                break;
            }
        }

        return count;
    }

    unsigned int EncoderBase64::Decrypt(unsigned char * dst, const unsigned char * src, unsigned int n) const
    {
        if (0 == n)
            return 0;

        unsigned int off = n % 4;
        if (1 == off)
            return 0;

        unsigned int count = (n >> 2) * 3;
        if (0 < off)
        {
            n -= off;
            count += (off - 1);
        }

        if (nullptr != dst && nullptr != src)
        {
            for (unsigned int i = 0; i < n; i += 4, src += 4, dst += 3)
            {
                dst[0] = ((_mapping[src[0]] & 0x3f) << 2) | ((_mapping[src[1]] & 0x30) >> 4);
                dst[1] = ((_mapping[src[1]] & 0x0f) << 4) | ((_mapping[src[2]] & 0x3c) >> 2);
                dst[2] = ((_mapping[src[2]] & 0x03) << 6) | (_mapping[src[3]] & 0x3f);
            }

            switch (off)
            {
            case 2:
                dst[0] = ((_mapping[src[0]] & 0x3f) << 2) | ((_mapping[src[1]] & 0x30) >> 4);
                break;
            case 3:
                dst[0] = ((_mapping[src[0]] & 0x3f) << 2) | ((_mapping[src[1]] & 0x30) >> 4);
                dst[1] = ((_mapping[src[1]] & 0x0f) << 4) | ((_mapping[src[2]] & 0x3c) >> 2);
                break;
            default:
                break;
            }
        }

        return count;
    }

}
