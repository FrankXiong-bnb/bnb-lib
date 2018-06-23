#ifdef _algorithm_api

template<typename _IterT, typename _FuncT>
bool NextPermutation(_IterT first, _IterT last, _FuncT pfun)
{
    _IterT prev = last;

    _bnb_assert_return( (!(first == last || first == --prev)), false);

    for ( ; ; )
    {
        _IterT next = prev;
        if ( pfun(*--prev, *next) )
        {
            _IterT iter = last;
            while ( !pfun(*prev, *--iter) );

            bnb::IterSwap(prev, iter);
            bnb::Reverse(next, last);

            return true;
        }

        if ( prev == first )
        {
            bnb::Reverse(first, last);

            return false;
        }
    }
}

template<typename _IterT>
bool NextPermutation(_IterT first, _IterT last)
{
    return NextPermutation(first, last, [](decltype(*first) left, decltype(*first) right){ return left < right; });
}

template<typename _IterT, typename _FuncT>
bool PrevPermutation(_IterT first, _IterT last, _FuncT pfun)
{
    _IterT prev = last;

    _bnb_assert_return( (!(first == last || first == --prev)), false);

    for ( ; ; )
    {
        _IterT next = prev;
        if ( pfun(*next, *--prev) )
        {
            _IterT iter = last;
            while ( !pfun(*--iter, *prev) );

            bnb::IterSwap(prev, iter);
            bnb::Reverse(next, last);

            return true;
        }

        if ( prev == first )
        {
            bnb::Reverse(first, last);

            return false;
        }
    }
}

template<typename _IterT>
bool PrevPermutation(_IterT first, _IterT last)
{
    return PrevPermutation(first, last, [](decltype(*first) left, decltype(*first) right){ return left < right; });
}

template<typename _FuncT, typename _Ty>
_size_t Permutation(_FuncT pfunc, const _Ty& obj, _size_t size, _size_t m = 1<<((sizeof(_size_t)<<3)-1))
{
    _bnb_assert_action( (size>m), (m=size) );
    _bnb_assert_return( m, 1 );
    
    auto _func_find = [](const _index_t* _ptr, const _size_t& _n, const _index_t& _val)->bool
                        {
                            for (_index_t _pos=0; _pos<_n; ++_pos)
                                if ( _val == _pos[_ptr] )
                                    return true;

                            return false;
                        };

    _index_t  _index = 0;
    _index_t* _stack = new _index_t[m];

    _size_t _count = 0;

    do
    {
        for (_index_t _pos = 0; _pos < size; ++_pos)
        {
            if ( !!!_func_find(_stack, _index, _pos) )
            {
                _stack[_index++] = _pos;
                break;
            }
        }

        for ( ; _index == m; ++_count)
        {
            pfunc(obj, _stack, m);            

            for (_index_t _pos = size; _pos >= size && _index; )
            {
                _pos = _stack[--_index];

                for (++_pos; _pos < size; ++_pos)
                {
                    if ( !!!_func_find(_stack, _index, _pos) )
                    {
                        _stack[_index++] = _pos;
                        break;
                    }
                }
            }
        }
    } while (_index);

    delete [] _stack;

    return _count;
}

template<typename _FuncT, typename _Ty, _size_t size>
inline _size_t Permutation(_FuncT pfunc, const _Ty (&arr)[size], _size_t m = size)
{
    return Permutation(pfunc, arr, size, m);
}

template<typename _FuncT, _size_t size>
inline _size_t Permutation(_FuncT pfunc, const char (&arr)[size], _size_t m = size - 1)
{
    return Permutation(pfunc, arr, size-1, m);
}

template<typename _FuncT, _size_t size>
inline _size_t Permutation(_FuncT pfunc, const chwr (&arr)[size], _size_t m = size - 1)
{
    return Permutation(pfunc, arr, size-1, m);
}


template<typename _FuncT, typename _Ty>
_index_t Combination(_FuncT pFunc, _Ty& obj, _size_t m, _size_t n)
{
    if (n > m) n = m;
    if (n == 0) return 1;

    _index_t _Pos = 0;
    _index_t _Index = 0;
    _index_t* _Stack = new _index_t[n];

    _size_t _Count = 0;
    const _index_t _X = m - n;

    do {
        _Stack[_Index++] = _Pos;

        for ( ; _Index == n; ++_Count)
        {
            pFunc(obj, const_cast<const _index_t*>(_Stack), _Index);

            for (_Pos = m; _Pos >= (_X + _Index) && _Index; )
            {
                _Pos = _Stack[--_Index] + 1;

                if (_Pos <= (_X + _Index))
                {
                    _Stack[_Index++] = _Pos;
                    break;
                }
            }
        }

        ++_Pos;
    } while (_Index);

    delete [] _Stack;

    return _Count;
}

#endif