#ifndef ____bnb_Stack_H_
#define ____bnb_Stack_H_

namespace bnb
{
    template<typename _Ty>
    class Stack
    {
        using value_type = _Ty;

    public:

        Stack(unsigned int n)
        {

        }

        bool Existing(const value_type& val) const
        {
            if (0 < _index)
            {
                const value_type* start = Data();

                for (unsigned int _pos = 0; _pos<_index; ++_pos)
                    if (_val == _pos[start])
                        return true;
            }

            return false;
        }

        void Push(const _Ty& val)
        {

        }



        const value_type* Data() const
        {
            if (_def_size < _capacity)
                return _stack._ptr;
            else
                return _stack._arr;
        }

        value_type* Data()
        {
            if (_def_size < _capacity)
                return _stack._ptr;
            else
                return _stack._arr;
        }




    private:
        static const unsigned int _def_size = 16;

        union {
            _charT  _arr[_def_size];
            _charT* _ptr;
        }_stack;


        unsigned int  _index;
        unsigned int  _capacity;

    };
}

#endif // ____bnb_Stack_H_
