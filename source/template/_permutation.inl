
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

class _simple_fix_stack
{
public:

    _simple_fix_stack(unsigned int n) : _size(n), _index(0) { _stack = new unsigned int[_size]; }
    ~_simple_fix_stack() { delete[] _stack; }

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
        return pfunc(nullptr, 0) ? 1 : 0;
    
    unsigned int _count = 0;

    _simple_fix_stack _sfs{ _n };

    do
    {
        for (unsigned int _pos = 0; _pos < _size; ++_pos)
        {
            if ( !!!_sfs.existing(_pos) )
            {
                _sfs.push(_pos);
                break;
            }
        }

        while (_sfs.is_full())
        {
            if (pfunc(_sfs.data(), _sfs.index()))
                ++_count;

            for (unsigned int _pos = _size; _size <= _pos && !_sfs.is_empty(); )
            {
                _pos = _sfs.pop();

                for (++_pos; _pos < _size; ++_pos)
                {
                    if (!!!_sfs.existing(_pos))
                    {
                        _sfs.push(_pos);
                        break;
                    }
                }
            }
        }
    } while (!_sfs.is_empty());

    return _count;
}

template<typename _FuncT>
unsigned int Combination(unsigned int _size, unsigned int _n, _FuncT pfunc)
{
    if (_n > _size)
        _n = _size;

    if (_n == 0)
        return pfunc(nullptr, 0) ? 1 : 0;

    unsigned int _Count = 0;
    const unsigned int _x = _size - _n;

    _simple_fix_stack _sfs{ _n };

    for (unsigned int _pos = 0; ; ++_pos)
    {
        _sfs.push(_pos);

        while (_sfs.is_full())
        {
            if (pfunc(_sfs.data(), _sfs.index()))
                ++_Count;

            for (_pos = _size; (_x + _sfs.index()) <= _pos && !_sfs.is_empty(); )
            {
                _pos = _sfs.pop() + 1;

                if (_pos <= (_x + _sfs.index()))
                {
                    _sfs.push(_pos);
                    break;
                }
            }
        }

        if (_sfs.is_empty())
            break;
    }

    return _Count;
}
