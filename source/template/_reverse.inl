
template<typename _IterT>
inline void Reverse(_IterT first, _IterT last)
{
    for (; first != last && first != --last; ++first)
        IterSwap(first, last);
}
