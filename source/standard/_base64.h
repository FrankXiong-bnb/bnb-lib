//=============================================================================
// Encoder with base64
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Base64_H_
#define ____bnb_Base64_H_

_bnb_space_in

class EncoderB64 : public _encoder_base
{
public:

    EncoderB64(const buf_type* alphabet = nullptr) { Appoint(alphabet); }

    bool Appoint(_in const buf_type* alphabet)
    {
        bool bAppoint = true;

        if (nullptr == alphabet || !_is_valid_alphabet(alphabet))
            alphabet = _gc_def_base_alphabet, bAppoint = false;

        for (size_type i=0; i < 64; ++i) _base_alphabet[i] = alphabet[i];
        for (size_type i=0; i < 256; ++i) _base_mapping[i] = 0xff;
        for (size_type i=0; i < 64; ++i) _base_mapping[_base_alphabet[i]] = i;

        return bAppoint;
    }

    virtual bool Encript(_in const buf_type* src, _in size_type size)
    {
        Reset();

        size_type off = size % 3;
        _size = (size / 3) << 2;

        if (off > 0)
        {
            size -= off;
            _size += (off + 1);
        }

        _result = new buf_type[_size];
        if ( !_result ) return false;

        buf_type* pos = _result;
        for (size_type index = 0; index < size; index += 3, src += 3, pos += 4)
        {
            pos[0] = _base_alphabet[(src[0] & 0xfc) >> 2];
            pos[1] = _base_alphabet[((src[0] & 0x03) << 4) | ((src[1] & 0xf0) >> 4)];
            pos[2] = _base_alphabet[((src[1] & 0x0f) << 2) | ((src[2] & 0xc0) >> 6)];
            pos[3] = _base_alphabet[src[2] & 0x3f];
        }

        if (off > 0)
        {
            buf_type arr3[3] = { 0 }, arr4[4] = { 0 };
            for (size_type i = 0; i < off; ++i) arr3[i] = src[i];

            arr4[0] = (arr3[0] & 0xfc) >> 2;
            arr4[1] = ((arr3[0] & 0x03) << 4) | ((arr3[1] & 0xf0) >> 4);
            arr4[2] = ((arr3[1] & 0x0f) << 2) | ((arr3[2] & 0xc0) >> 6);
            arr4[3] = arr3[2] & 0x3f;
            arr4[off] += off;

            for (size_type i = 0; i <= off; ++i) pos[i] = _base_alphabet[arr4[i]];
        }

        return true;
    }

    virtual bool Decript(_in const buf_type* src, _in size_type size)
    {
        Reset();

        size_type off = size % 4;
        if (1 == off) return false;

        _size = (size>>2) * 3;

        if (off > 0)
        {
            size -= off;
            _size += (off - 1);
        }

        _result = new buf_type[_size];
        if ( !_result ) return false;

        buf_type* pos = _result;
        for (size_type index = 0; index < size; index += 4, src += 4, pos += 3)
        {
            pos[0] = ((_base_mapping[src[0]] & 0x3f) << 2) | ((_base_mapping[src[1]] & 0x30) >> 4);
            pos[1] = ((_base_mapping[src[1]] & 0x0f) << 4) | ((_base_mapping[src[2]] & 0x3c) >> 2);
            pos[2] = ((_base_mapping[src[2]] & 0x03) << 6) | (_base_mapping[src[3]] & 0x3f);
        }

        if (off > 0)
        {
            buf_type arr3[3] = { 0 }, arr4[4] = { 0 };
            for (size_type i = 0; i < off; ++i) arr4[i] = _base_mapping[src[i]];

            arr3[0] = ((arr4[0] & 0x3f) << 2) | ((arr4[1] & 0x30) >> 4);
            arr3[1] = ((arr4[1] & 0x0f) << 4) | ((arr4[2] & 0x3c) >> 2);
            arr3[2] = ((arr4[2] & 0x03) << 6) | (arr4[3] & 0x3f);

            for (size_type i = 0; i < off - 1; ++i) pos[i] = arr3[i];
        }

        return true;
    }

private:

    bool _is_valid_alphabet(_in const buf_type* alphabet)
    {
        for (size_type i=0; i<64; ++i)
            for (size_type j=i+1; j<64; ++j)
                if (alphabet[i] == alphabet[j])
                    return false;

        return true;
    }  

    buf_type    _base_alphabet[64];
    buf_type    _base_mapping[256];

};  // class EncoderB64

_bnb_space_out

#endif