
template<typename _IterT, typename _Ty>
inline _IterT Remove(_IterT first, _IterT last, const _Ty& val)
{
    first = Find(first, last, val);
    _IterT _next = first;
    if (first != last)
    {
        for (++first; first != last; ++first)
            if (!(*first == val))
                *_next++ = Move(*first);
    }

    return (_next);
}

template<typename _IterT, typename _FuncT>
inline _IterT RemoveIf(_IterT first, _IterT last, _FuncT& pfun)
{
    first = FindIf(first, last, pfun);
    _IterT _next = first;
    if (first != last)
    {
        for (++first; first != last; ++first)
            if (!pfun(*first))
                *_next++ = Move(*first);
    }

    return (_next);
}
