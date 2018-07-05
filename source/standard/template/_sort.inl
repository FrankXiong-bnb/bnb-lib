
template<typename _Ty, typename _LessT>
inline void _Adjust_Heap(_Ty* _Head, unsigned int _Hole, unsigned int _Size, _LessT _pFunc)
{
    unsigned int _index = (_Hole << 1) + 2;

    while (_index < _Size)
    {
        if (_pFunc(_Head[_index], _Head[_index - 1]))
            --_index;

        if (_pFunc(_Head[_Hole], _Head[_index]))
            Swap(_Head[_Hole], _Head[_index]);
        else
            return ;

        _Hole = _index;
        _index = (_Hole << 1) + 2;
    }

    if (_index == _Size)
        if (_pFunc(_Head[_Hole], _Head[_index -1 ]))
            Swap(_Head[_Hole], _Head[_index - 1]);
}

template<typename _Ty>
inline void _Adjust_Heap(_Ty* _Head, unsigned int _Hole, unsigned int _Size)
{
    _Adjust_Heap(_Head, _Hole, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
inline void _Heap_Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    for (unsigned int _Hole = _Size>>1; 0 < _Hole--; )
        _Adjust_Heap(_Head, _Hole, _Size, _pFunc);

    for ( --_Size; 0 < _Size; --_Size)
    {
        Swap(_Head[0], _Head[_Size]);
        _Adjust_Heap(_Head, 0, _Size, _pFunc);
    }
}

template<typename _Ty, typename _LessT>
inline void _Selection_Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{    
    for (unsigned int maxpos = 0, _index = 0; 0 < _Size; )
    {
        maxpos = 0;
        for (_index = 1; _index < _Size; ++_index)
            if (_pFunc(_Head[maxpos], _Head[_index]))
                maxpos = _index;

        Swap(_Head[--_Size], _Head[maxpos]);
    }
}

template<typename _Ty, typename _LessT>
inline void _Quick_Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    unsigned int _sl[0x20] = { 0 }, _sr[0x20] = { 0 };
    unsigned int lastL = 0, lastR = _Size - 1;
    unsigned int nextL = 0, nextR = 0;
    unsigned int mid = 0;

    unsigned int _n = 0;
    int _s_top = 0;

    for ( ; ; ) {
        _n = lastR - lastL + 1;

        if (_n < 8) {
            _Selection_Sort(_Head + lastL, _n, _pFunc);
        }
        else {
            nextL = lastL;
            nextR = lastR;
            mid = ((nextL + nextR) >> 1);

            if (_pFunc(_Head[mid], _Head[nextL])) Swap(_Head[mid], _Head[nextL]);
            if (_pFunc(_Head[nextR], _Head[nextL])) Swap(_Head[nextR], _Head[nextL]);
            if (_pFunc(_Head[nextR], _Head[mid])) Swap(_Head[nextR], _Head[mid]);

            for ( ; ; ) {
                for ( ++nextL; nextL < nextR && !_pFunc(_Head[mid], _Head[nextL]); ++nextL);
                for ( ; mid < nextR && _pFunc(_Head[mid], _Head[nextR]); --nextR);

                if (nextR < nextL) break;

                Swap(_Head[nextR], _Head[nextL]);

                if (mid == nextR) mid = nextL;
            }

            for ( ; lastL < nextR && !_pFunc(_Head[nextR], _Head[mid]); --nextR);

            if (nextR - lastL < lastR - nextL) {
                if (nextL < lastR) {
                    _sl[_s_top] = nextL;
                    _sr[_s_top] = lastR;
                    ++_s_top;
                }

                if (lastL < nextR) {
                    lastR = nextR;
                    continue;
                }
            } 
            else {
                if (lastL < nextR) {
                    _sl[_s_top] = lastL;
                    _sr[_s_top] = nextR;
                    ++_s_top;
                }

                if (nextL < lastR) {
                    lastL = nextL;
                    continue;
                }
            }
        }

        if (_s_top == 0)
            break;
        else
            --_s_top;

        lastL = _sl[_s_top];
        lastR = _sr[_s_top];
    }
}

template<typename _Ty, typename _LessT>
inline void _Bubble_Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    for (unsigned int i = 0; i < _Size; ++i)
        for (unsigned int j = i + 1; j < _Size; ++j)
            if (_pFunc(_Head[j], _Head[i]))
                Swap(_Head[j], _Head[i]);
}

template<typename _Ty, typename _LessT>
inline void _Insertion_Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    for (unsigned int i = 1; i < _Size; ++i)
    {
        _Ty* next = _Head + i, key(*next);

        if (_pFunc(key, *_Head))
        {
            for (_Ty* last = next; next != _Head; next = last)
                *next = *--last;

            *_Head = key;
        } 
        else
        {
            for (_Ty* last = next; _pFunc(key, *--last); next = last)
                *next = *last;

            *next = key;
        }
    }
}

template<typename _Ty, typename _LessT>
inline void HeapSort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    if (_Head != nullptr && 1 < _Size)
        _Heap_Sort(_Head, _Size, _pFunc);
}

template<typename _Ty>
inline void HeapSort(_Ty* _Head, unsigned int _Size)
{
    if (_Head != nullptr && 1 < _Size)
        _Heap_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right) { return left < right; });
}

template<typename _Ty, typename _LessT>
inline void SelectionSort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    if (_Head != nullptr && 1 < _Size)
        _Selection_Sort(_Head, _Size, _pFunc);
}

template<typename _Ty>
inline void SelectionSort(_Ty* _Head, unsigned int _Size)
{
    if (_Head != nullptr && 1 < _Size)
        _Selection_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right) { return left < right; });
}

template<typename _Ty, typename _LessT>
inline void BubbleSort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    if (_Head != nullptr && 1 < _Size)
        _Bubble_Sort(_Head, _Size, _pFunc);
}

template<typename _Ty>
inline void BubbleSort(_Ty* _Head, unsigned int _Size)
{
    if (_Head != nullptr && 1 < _Size)
        _Bubble_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right) { return left < right; });
}

template<typename _Ty, typename _LessT>
inline void InsertionSort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    if (_Head != nullptr && 1 < _Size)
        _Insertion_Sort(_Head, _Size, _pFunc);
}

template<typename _Ty>
inline void InsertionSort(_Ty* _Head, unsigned int _Size)
{
    if (_Head != nullptr && 1 < _Size)
        _Insertion_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right) { return left < right; });
}

template<typename _Ty, typename _LessT>
inline void QuickSort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    if (_Head != nullptr && 1 < _Size)
        _Quick_Sort(_Head, _Size, _pFunc);
}

template<typename _Ty>
inline void QuickSort(_Ty* _Head, unsigned int _Size)
{
    if (_Head != nullptr && 1 < _Size)
        _Quick_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right) { return left < right; });
}

template<typename _Ty>
inline void Sort(_Ty* _Head, unsigned int _Size)
{
    InsertionSort(_Head, _Size);
}

template<typename _Ty, typename _LessT>
inline void Sort(_Ty* _Head, unsigned int _Size, _LessT _pFunc)
{
    InsertionSort(_Head, _Size, _pFunc);
}
