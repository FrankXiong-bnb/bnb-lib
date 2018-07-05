#ifndef ____bnb_Algorithm_H_
#define ____bnb_Algorithm_H_

#include "template/_template.h"
#include "template/_type_traits.h"

namespace bnb
{
    // �ƶ�
    template<class _Ty>
    inline constexpr typename remove_reference<_Ty>::type&& Move(_Ty&& _arg) noexcept
    {
        return (static_cast<typename remove_reference<_Ty>::type&&>(_arg));
    }

    // ת��
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

    // ����
#include "template/_find.inl"

    // ����
#include "template/_swap.inl"

    // ɾ��
#include "template/_remove.inl"

    // �滻
#include "template/_replace.inl"

    // ��ת
#include "template/_reverse.inl"

    // ����
#include "template/_sort.inl"

    // ����-���
#include "template/_permutation.inl"

    // ����
    // ����
    // �Ƚ�
    // ͳ��
    // �ϲ�
    // ����

}

#endif  // ____bnb_Algorithm_H_
