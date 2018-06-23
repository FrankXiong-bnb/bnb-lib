#ifndef ____bnb_Poker_Assistant_H_
#define ____bnb_Poker_Assistant_H_

#include <iostream>

#include "pk_Define.h"

_poker_space_in

#define _pkTextCount    5

// 花色文字
const char* _gc_text_flower[]{
    "方", "梅", "心", "桃", "王"
};
// 点数文字
const char* _gc_text_number[]{
    "None", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "小王", "大王"
};

// 生成单张扑克字符串
inline void MakePokerText(char* str, const _pk_t& k)
{
    _pk_flower_t flower(_pkFlower(k));
    _pk_number_t number(_pkNumber(k));

    if (_fK < flower || _nNone == number)
    {
        sprintf_s(str, _pkTextCount + 1, " None");
        return;
    }

    switch (number)
    {
        case _nS:
        case _nB:
        {
            if (_fK == flower)
                sprintf_s(str, _pkTextCount + 1, " %s", _gc_text_number[number]);
            else
                sprintf_s(str, _pkTextCount + 1, " None");

            break;
        }
        case _nT:
            sprintf_s(str, _pkTextCount + 1, " %s%s", _gc_text_flower[_fpkIndex(k)], _gc_text_number[number]);
            break;
        default:
            sprintf_s(str, _pkTextCount + 1, " %s_%s", _gc_text_flower[_fpkIndex(k)], _gc_text_number[number]);
            break;
    }
}

// 生成扑克组字符串
inline void MakePokerText(char* str, _size_t len, const _pk_t* pk, _size_t n)
{
    for (_index_t i = 0; i < n && (_pkTextCount * (i + 1)) < len; ++i)
        MakePokerText(str + (_pkTextCount * i), pk[i]);
}

template<_size_t n>
inline void MakePokerText(char* str, _size_t len, const _pk_t(&pk)[n])
{
    MakePokerText(str, len, pk, n);
}

// 显示扑克数组
inline void ShowPokerArray(std::ostream& os, const _pk_t* pk, _size_t n)
{
    _array_t<char, 0x80> str{ 0 };
    MakePokerText(str, 0x80, pk, n);
    os << str << std::endl;
}

template<_size_t n>
inline void ShowPokerArray(std::ostream& os, const _pk_t(&arr)[n])
{
    ShowPokerArray(os, arr, n);
}

bool _StringToPoker(_pk_t& k, const char* str)
{
    _pk_t l = static_cast<_pk_t>(strtoul(str, nullptr, 16));
    if (_pkNumber(l) && _pkFlower(l) < _fNone)
    {
        k = l;
        return true;
    }

    return false;
}

_size_t StringToPoker(_pk_t* pk, _size_t n, const char* str, const char& key)
{
    _size_t i = 0;

    while (i < n)
    {
        if (_StringToPoker(pk[i], str))
            ++i;
        else
            break;

        if (str = strchr(str, key))
            ++str;
        else
            break;
    }

    return i;
}

_poker_space_out

#endif
