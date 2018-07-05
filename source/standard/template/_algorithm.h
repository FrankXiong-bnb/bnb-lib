#ifndef ____bnb_Algorithm_H_
#define ____bnb_Algorithm_H_

#include "template/_template.h"
#include "template/_type_traits.h"

namespace bnb
{
    // 移动
    template<class _Ty>
    inline constexpr typename remove_reference<_Ty>::type&& Move(_Ty&& _arg) noexcept
    {
        return (static_cast<typename remove_reference<_Ty>::type&&>(_arg));
    }

    // 转发
    template<class _Ty>
    inline constexpr _Ty&& Forward(typename remove_reference<_Ty>::type& _Arg) noexcept
    {
        return (static_cast<_Ty&&>(_Arg));
    }

    template<class _Ty>
    inline constexpr _Ty&& Forward(typename remove_reference<_Ty>::type&& _Arg) noexcept
    {
        static_assert(!is_lvalue_reference<_Ty>::value, "bad forward call");
        return (static_cast<_Ty&&>(_Arg));
    }

    // 查找
#include "template/_find.inl"

    // 交换
#include "template/_swap.inl"

    // 删除
#include "template/_remove.inl"

    // 替换
#include "template/_replace.inl"

    // 反转
#include "template/_reverse.inl"

    // 排序
#include "template/_sort.inl"

    // 排列-组合
#include "template/_permutation.inl"

    // 插入
    // 复制
    // 比较
    // 统计
    // 合并
    // 遍历

}

#endif  // ____bnb_Algorithm_H_
