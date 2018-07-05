
template<typename _Ty>
inline void Swap(_Ty& left, _Ty& right)
{
    _Ty _tmp = Move(left);
    left = Move(right);
    right = Move(_tmp);
}

template<typename _IterT>
inline void IterSwap(_IterT left, _IterT right)
{
    Swap(*left, *right);
}

template<typename _Ty, unsigned int _size>
inline void Swap(_Ty(&left)[_size], _Ty(&right)[_size])
{
    if (&left != &right)
    {
        _Ty *last = left + _size;
        for (_Ty *first = left, *start = right; first != last; ++first, ++start)
            IterSwap(first, start);
    }
}

