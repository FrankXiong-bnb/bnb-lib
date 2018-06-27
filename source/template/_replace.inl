
template<typename _FwdIt, typename _Ty>
inline unsigned int _Replace(_FwdIt _First, _FwdIt _Last, const _Ty& _Oldval, const _Ty& _Newval)
{
    unsigned int n = 0;
    for (; _First != _Last; ++_First)
    {
        if (*_First == _Oldval)
        {
            *_First = _Newval;
            ++n;
        }
    }

    return n;
}

template<typename _FwdIt, typename _Ty, typename _FuncT>
inline unsigned int _ReplaceIf(_FwdIt _First, _FwdIt _Last, _FuncT& _pFunc, const _Ty& _Val)
{
    unsigned int n = 0;
    for (; _First != _Last; ++_First)
    {
        if (_pFunc(*_First))
        {
            *_First = _Val;
            ++n;
        }
    }

    return n;
}

template<typename _FwdIt, typename _Ty>
inline unsigned int Replace(_FwdIt _First, _FwdIt _Last, const _Ty& _Oldval, const _Ty& _Newval)
{
    return _Replace(_First, _Last, _Oldval, _Newval);
}

template<typename _FwdIt, typename _Ty, typename _FuncT>
inline unsigned int ReplaceIf(_FwdIt _First, _FwdIt _Last, _FuncT& _pFunc, const _Ty& _Val)
{
    return _ReplaceIf(_First, _Last, _pFunc, _Val);
}

template<typename _Ty>
inline unsigned int Replace(_Ty* _Head, unsigned int _Size, const _Ty& oldVal, const _Ty& newVal)
{
    return _Replace(_Head, _Head + _Size, oldVal, newVal);
}

template<typename _Ty, typename _FuncT>
unsigned int ReplaceIf(_Ty* _Head, unsigned int _Size, _FuncT _pFunc, const _Ty& _Val)
{
    return _ReplaceIf(_Head, _Head + _Size, _pFunc, _Val);
}

template<typename _Ty, unsigned int _Size>
inline unsigned int Replace(_Ty (&_Head)[_Size], const _Ty& oldVal, const _Ty& newVal)
{
    return _Replace(_Head, _Head + _Size, oldVal, newVal);
}

template<typename _Ty, unsigned int _Size, typename _FuncT>
unsigned int ReplaceIf(_Ty(&_Head)[_Size], _FuncT _pFunc, const _Ty& _Val)
{
    return _ReplaceIf(_Head, _Head + _Size, _pFunc, _Val);
}


