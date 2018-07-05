//=============================================================================
// The default encryption mapping alphabet
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Encrypt_H_
#define ____bnb_Encrypt_H_

namespace bnb
{
    unsigned int Base64Encrypt(unsigned char* dst, const unsigned char* src, unsigned int n);
    unsigned int Base64Decrypt(unsigned char* dst, const unsigned char* src, unsigned int n);

    unsigned int RC4Encoding(unsigned char* dst, const unsigned char* src, unsigned int n, const unsigned char* key, unsigned int nKey);

    void SHA256(unsigned char(&digest)[0x20], const unsigned char* str, unsigned int n);
    void MD5(unsigned char(&digest)[0x10], const unsigned char* str, unsigned int n);

    void _to_hex_str(unsigned char* dst, const unsigned char* src, unsigned int n);
    inline unsigned int HexCharacter(unsigned char* dst, const unsigned char* src, unsigned int n)
    {
        if (nullptr != dst && nullptr != src && 0 < n)
            _to_hex_str(dst, src, n);

        return n << 1;
    }

    inline unsigned int _hash_seq(const unsigned char *ptr, unsigned int n)
    {
        unsigned int _value = 2166136261u;

        for (unsigned int i = 0; i < n; ++i)
        {
            _value ^= static_cast<unsigned int>(ptr[i]);
            _value *= 16777619u;
        }

        return (_value);
    }

    template<unsigned int n>
    inline void DigestToSignature(unsigned char(&str)[n << 1], const unsigned char(&arr)[n])
    {
        _to_hex_str(str, arr, n);
    }

}

#include "encrypt/_base64.h"

#endif  // ____bnb_Encrypt_H_
