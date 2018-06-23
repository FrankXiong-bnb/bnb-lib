
#include <iostream>

#include "pk_Assistant.h"
#include "pk_ddz_ai.h"

using namespace _ns_poker;
using namespace _ns_utils;
using namespace _ns_ddz;
using namespace _ns_ddzai;

const char* _gc_type_text[dpt_max] = {
    "未知", "单牌", "对子", "三条", "顺子", "连对", "飞机", "三带一", "三带二",
    "飞机带翅膀1", "飞机带翅膀2", "四带二", "炸弹", "火箭"
};

template<typename _Ty>
void ShowArray(const _Ty* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << int(arr[i]) << " ";
    }

    std::cout << std::endl;
}

template<typename _Ty, _size_t n>
void ShowArray(const _Ty (&arr)[n])
{
    ShowArray(arr, n);
}

void ShowArray(const _pk_t* arr, _size_t n)
{
    ShowPokerArray(std::cout, arr, n);
}

void ShowPkarr(const _pkarr_t& item)
{
    std::cout << _gc_type_text[item.GetType()] << ": ";
    ShowPokerArray(std::cout, item.GetPoker(), item.GetCount());
}

void ShowPklist(const _pklist_t& pklist)
{
    pklist.ForeachForward(ShowPkarr);
}


const _pk_t src[_ddzMaxCount] = {
    _fF | _n3, _fF | _n4, _fF | _n5, _fF | _n6,
    _fM | _n7, _fM | _n8, _fM | _nJ, _fM | _n5,
    _fX | _n6, _fX | _n9, _fX | _nT, _fX | _nQ,
    _fT | _n7, _fT | _nT, _fT | _nJ, _fM | _nK,
    _fK | _nS, _fF | _n2, _fM | _n2, _fT | _nA
};


int main()
{
    _pklist_t pklist;

    //ddzSplitList(pklist, src, 20);

    //ShowPklist(pklist);

    std::cout << sizeof(void*) << std::endl;
    std::cout << sizeof(long long int) << std::endl;

    return (0);
}
