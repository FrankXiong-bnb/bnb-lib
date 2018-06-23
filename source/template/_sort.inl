#ifdef _algorithm_api

#define _size_stack_quick       (8 * sizeof(int))
#define _bound_sort_select      32
#define _bound_quick_select     8

template<typename _Ty, typename _LessT>
void _Adjust_Heap(_Ty* _Head, _size_t _Hole, _size_t _Size, _LessT _pFunc)
{
    _size_t _index = (_Hole << 1) + 2;

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
void _Adjust_Heap(_Ty* _Head, _size_t _Hole, _size_t _Size)
{
    _Adjust_Heap(_Head, _Hole, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
void _Heap_Sort(_Ty* _Head, _size_t _Size, _LessT _pFunc)
{
    for (_size_t _Hole = _Size>>1; _Hole-- > 0; )
        _Adjust_Heap(_Head, _Hole, _Size, _pFunc);

    for ( --_Size; _Size > 0; --_Size)
    {
        Swap(_Head[0], _Head[_Size]);
        _Adjust_Heap(_Head, 0, _Size, _pFunc);
    }
}

template<typename _Ty>
void _Heap_Sort(_Ty* _Head, _size_t _Size)
{
    _Heap_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
void _Selection_Sort(_Ty* _Head, _size_t _Size, _LessT _pFunc)
{    
    for (_index_t maxpos = 0, _index = 0; _Size > 0; )
    {
        maxpos = 0;
        for (_index = 1; _index < _Size; ++_index)
            if (_pFunc(_Head[maxpos], _Head[_index]))
                maxpos = _index;

        Swap(_Head[--_Size], _Head[maxpos]);
    }
}

template<typename _Ty>
void _Selection_Sort(_Ty* _Head, _size_t _Size)
{    
    _Selection_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
void _Quick_Sort(_Ty* _Head, _size_t _Size, _LessT _pFunc)
{
    _index_t _sl[_size_stack_quick] = { 0 }, _sr[_size_stack_quick] = { 0 };
    _index_t lastL = 0, lastR = _Size - 1;
    _index_t nextL = 0, nextR = 0;
    _index_t mid = 0;

    _size_t _n = 0;
    int _s_top = 0;

    for ( ; ; ) {
        _n = lastR - lastL + 1;

        if (_n < _bound_quick_select) {
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

            for ( ; nextR > lastL && !_pFunc(_Head[nextR], _Head[mid]); --nextR);

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

        if (--_s_top < 0) break;

        lastL = _sl[_s_top];
        lastR = _sr[_s_top];
    }
}

template<typename _Ty>
void _Quick_Sort(_Ty* _Head, _size_t _Size)
{    
    _Quick_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
void _Bubble_Sort(_Ty* _Head, _size_t _Size, _LessT _pFunc)
{
    for (_index_t i = 0; i < _Size; ++i)
        for (_index_t j = i + 1; j < _Size; ++j)
            if (_pFunc(_Head[j], _Head[i]))
                Swap(_Head[j], _Head[i]);
}

template<typename _Ty>
void _Bubble_Sort(_Ty* _Head, _size_t _Size)
{    
    _Bubble_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty, typename _LessT>
void _Insertion_Sort(_Ty* _Head, _size_t _Size, _LessT _pFunc)
{
    for (_index_t i = 1; i < _Size; ++i)
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

template<typename _Ty>
void _Insertion_Sort(_Ty* _Head, _size_t _Size)
{    
    _Insertion_Sort(_Head, _Size, [](const _Ty& left, const _Ty& right){ return left < right; });
}

template<typename _Ty>
void _Sort(_Ty* _Head, _size_t _Size)
{
    if (_Size < 2) return;

    _Insertion_Sort(_Head, _Size);
}

#endif