
template<typename _IterT, typename _FuncT>
bool NextPermutation(_IterT first, _IterT last, _FuncT pfun)
{
    _IterT prev = last;

    if ((first == last || first == --prev))
        return false;

    for ( ; ; )
    {
        _IterT next = prev;
        if ( pfun(*--prev, *next) )
        {
            _IterT iter = last;
            while ( !pfun(*prev, *--iter) );

            IterSwap(prev, iter);
            Reverse(next, last);

            return true;
        }

        if ( prev == first )
        {
            Reverse(first, last);

            return false;
        }
    }
}

template<typename _IterT>
bool NextPermutation(_IterT first, _IterT last)
{
    using _Ty = decltype(*first);
    return NextPermutation(first, last, [](_Ty&& left, _Ty&& right){ return left < right; });
}

template<typename _IterT, typename _FuncT>
bool PrevPermutation(_IterT first, _IterT last, _FuncT pfun)
{
    _IterT prev = last;

    if ((first == last || first == --prev))
        return false;

    for ( ; ; )
    {
        _IterT next = prev;
        if ( pfun(*next, *--prev) )
        {
            _IterT iter = last;
            while ( !pfun(*--iter, *prev) );

            IterSwap(prev, iter);
            Reverse(next, last);

            return true;
        }

        if ( prev == first )
        {
            Reverse(first, last);

            return false;
        }
    }
}

template<typename _IterT>
bool PrevPermutation(_IterT first, _IterT last)
{
    using _Ty = decltype(*first);
    return PrevPermutation(first, last, [](_Ty&& left, _Ty&& right){ return left < right; });
}

class _simple_stack
{
public:

    _simple_stack(unsigned int n) : _size(n), _index(0) { _stack = new unsigned int[_size]; }
    ~_simple_stack() { delete[] _stack; }

    void push(const unsigned int& val) { _stack[_index++] = val; }
    unsigned int pop() { return _stack[--_index]; }

    bool is_full() const { return (_index == _size); }
    bool is_empty() const { return (_index == 0); }

    const unsigned int* data() const { return _stack; }
    unsigned int index() const { return _index; }

    bool existing(const unsigned int& val) const
    {
        for (unsigned int _pos = 0; _pos<_index; ++_pos)
            if (val == _pos[_stack])
                return true;

        return false;
    }

private:

    unsigned int* _stack;
    unsigned int _index;
    const unsigned int _size;

};

template<typename _FuncT>
unsigned int Permutation(unsigned int _size, unsigned int _n, _FuncT pfunc)
{
    if (_n > _size)
        _n = _size;

    if (_n == 0)
        return 1;
    
    unsigned int _count = 0;

    _simple_stack _ss{ _n };

    do
    {
        for (unsigned int _pos = 0; _pos < _size; ++_pos)
        {
            if ( !!!_ss.existing(_pos) )
            {
                _ss.push(_pos);
                break;
            }
        }

        while (_ss.is_full())
        {
            if (pfunc(_ss.data(), _ss.index()))
                ++_count;

            for (unsigned int _pos = _size; _size <= _pos && !_ss.is_empty(); )
            {
                _pos = _ss.pop();

                for (++_pos; _pos < _size; ++_pos)
                {
                    if (!!!_ss.existing(_pos))
                    {
                        _ss.push(_pos);
                        break;
                    }
                }
            }
        }
    } while (!_ss.is_empty());

    return _count;
}

template<typename _FuncT, typename _Ty>
unsigned int Combination(_FuncT pFunc, _Ty& obj, unsigned int m, unsigned int n)
{
    if (n > m) n = m;
    if (n == 0) return 1;

    unsigned int _Pos = 0;
    unsigned int _Index = 0;
    unsigned int* _Stack = new unsigned int[n];

    unsigned int _Count = 0;
    const unsigned int _X = m - n;

    do {
        _Stack[_Index++] = _Pos;

        for ( ; _Index == n; ++_Count)
        {
            pFunc(obj, const_cast<const unsigned int*>(_Stack), _Index);

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
