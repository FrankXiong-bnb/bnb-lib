#ifndef ____bnb_Smart_Buffer_H_
#define ____bnb_Smart_Buffer_H_

namespace bnb
{

    template<typename _Ty>
    struct _smart_buf
    {
        typedef _smart_buf<_Ty>     _sbType;
        typedef _Ty                 value_type;
        typedef unsigned int        size_type;
        typedef unsigned int        pos_type;

        enum {
            _def_size = 2,
            _max_size = 2,
            _invalid_pos = 3
        };

        union {
            value_type*    _ptr;
            value_type     _arr[_def_size];
        };

        size_type   _size;
        size_type   _capacity;

        void Clear();
        bool Extend();
    };



}

#endif
