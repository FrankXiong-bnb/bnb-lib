#ifndef ____bnb_Algorithm_h_
#define ____bnb_Algorithm_h_

// 插入

// 删除

// 复制

// 替换

// 查找

// 移动

// 交换

// 反转

// 比较

// 排序

// 排列

// 组合

// 统计

// 合并



_bnb_space_in
/*
template<typename _Ty>
void Copy();

template<typename _Ty>
void Compare();

void Insert();

void Delete();

void Replace();

void ForEach();

void Begin();

void End();
*/
template<typename _Ty>
inline void Swap(_Ty& left, _Ty& right)
{
    _Ty _temp(left);
    left    = right;
    right   = _temp;
}

template<typename _Ty>
inline void Swap(_Ty* left, _Ty* right)
{
    Swap(*left, *right)
}

template<typename _IterT>
inline void IterSwap(_IterT left, _IterT right)
{
    Swap(*left, *right);
}

template<typename _IterT>
_IterT Remove(_IterT first, _IterT last) { }


template<typename _IterT>
inline void Reverse(_IterT first, _IterT last)
{
    for ( ; first != last && first != --last; ++first)
        IterSwap(first, last);
}


template<typename _Ty1, typename _Ty2>
void Reverse(_Ty1 first, _Ty1 last, _Ty2 dst)
{

}

#ifndef _algorithm_api
#define _algorithm_api

// ...

#include "../template/_find.inl"

#include "../template/_replace.inl"

#include "../template/_permutation.inl"

#include "../template/_sort.inl"

#undef  _algorithm_api

#endif

_bnb_space_out

#endif