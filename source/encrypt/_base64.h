//=============================================================================
// Encoder with base64
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Base64_H_
#define ____bnb_Base64_H_

namespace bnb
{

    unsigned int Base64Encrypt(unsigned char* dst, const unsigned char* src, unsigned int n);
    unsigned int Base64Decrypt(unsigned char* dst, const unsigned char* src, unsigned int n);

    class EncoderBase64
    {
    public:

        EncoderBase64(const unsigned char(&_map)[64]);

        unsigned int Encrypt(unsigned char* dst, const unsigned char* src, unsigned int n) const;
        unsigned int Decrypt(unsigned char* dst, const unsigned char* src, unsigned int n) const;

        bool Appoint(const unsigned char(&_map)[64])
        {
            if (CheckAlphabet(_map))
            {
                _appoint(_map);
                return true;
            }

            return false;
        }

        static bool CheckAlphabet(const unsigned char(&alphabet)[64])
        {
            unsigned char _map[32]{ 0 };
            for (const unsigned char x : alphabet)
            {
                unsigned int index = x >> 3;
                unsigned char val = 1 << (x & 7);
                if ((_map[index] & val) != 0)
                    return false;

                _map[index] |= val;
            }

            return true;
        }

    private:

        void _appoint(const unsigned char(&_map)[64])
        {
            for (unsigned int i = 0; i < 64; ++i) _alphabet[i] = _map[i];
            for (unsigned int i = 0; i < 256; ++i) _mapping[i] = 0x00;
            for (unsigned int i = 0; i < 64; ++i) _mapping[_alphabet[i]] = i;
        }

        unsigned char _alphabet[64];
        unsigned char _mapping[256];

    };  // class EncoderBase64

}

#endif
