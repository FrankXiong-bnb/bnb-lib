//=============================================================================
// Encoder with key
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Encoder_Key_H_
#define ____bnb_Encoder_Key_H_

_bnb_space_in

template<_encoder_base::size_type _buf_size = 0x10>
class EncoderKey : public _encoder_base
{
public:

    EncoderKey(const buf_type* alphabet = nullptr)
    {
        static_assert(_buf_size>1, "The _buf_size can't less than 2");
        static_assert(_buf_size<33, "The _buf_size can't greater than 32");

        Appoint(alphabet);
    }

    bool Appoint(_in const buf_type* alphabet)
    {
        bool bAppoint = true;

        if (nullptr == alphabet)
            alphabet = _gc_def_key_alphabet, bAppoint = false;

        for (size_type i = 0; i < _buf_size; ++i)
            _key_buf[i] = alphabet[i];

        return bAppoint;
    }
    
    virtual bool Encript(_in const buf_type* src, _in size_type size)
    {
        Reset();

        if ( !src || !size ) return false;
        
        _size = size;
        _result = new buf_type[_size];
        if ( !_result ) return false;

        buf_type last = _key_buf[0];

        for (size_type i = 0; i < size; ++i)
        {
            _result[i] = _gc_def_map_table1[buf_type(src[i] - _key_buf[i % _buf_size] - last)];
            last = _result[i];
        }

        return true;
    }

    virtual bool Decript(_in const buf_type* src, _in size_type size)
    {
        Reset();

        if ( !src || !size ) return false;

        _size = size;
        _result = new buf_type[_size];
        if ( !_result ) return false;

        for (size_type i = size-1; i > 0; --i)
            _result[i] = _gc_def_map_table2[src[i]] + src[i-1] + _key_buf[i % _buf_size];

        _result[0] = _gc_def_map_table2[src[0]] + _key_buf[0] + _key_buf[0];

        return true;
    }
    
private:

    buf_type    _key_buf[_buf_size];

};  // class EncoderKey

_bnb_space_out

#endif