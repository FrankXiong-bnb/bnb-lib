//=============================================================================
// Encoder Base
//                                                          2014-8 by Frank
//=============================================================================
#ifndef ____bnb_Encoder_Base_H_
#define ____bnb_Encoder_Base_H_

_bnb_space_in

class _encoder_base
{
public:

    typedef unsigned char   buf_type;
    typedef unsigned int    size_type;

    virtual ~_encoder_base() { Reset(); }
    _encoder_base() : _result(nullptr), _size(0) { }

    void Reset() { if (_result) delete [] _result; _result = nullptr; _size = 0; }

    size_type GetSize() const { return _size; }
    const buf_type* GetData() const { return _result; }

    size_type CopyResult(_out buf_type* buf, _in size_type size) const
    {
        if (nullptr == buf || nullptr == _result) return 0;
        size_type count = _size < size ? _size : size;
        for (size_type i = 0; i < count; ++i)
            buf[i] = _result[i];

        return count;
    }

    virtual bool Encript(_in const buf_type* src, _in size_type size)
    {
        Reset();

        if (nullptr == src || 0 == size) return false;

        _result = new buf_type[size];
        if (_result == nullptr) return false;        

        for (_size = size; size; )
            --size, _result[size] = src[size];

        return true;
    }

    virtual bool Decript(_in const buf_type* src, _in size_type size) { return Encript(src, size); }
    
protected:

    buf_type*   _result;
    size_type   _size;

};  //  class _encoder_base

_bnb_space_out

#endif
//=============================================================================
// 
//=============================================================================
