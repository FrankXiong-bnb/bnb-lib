#ifndef ____bnb_Type_Traits_H_
#define ____bnb_Type_Traits_H_

namespace bnb
{
    template<class _Ty>
    struct is_array : false_type { };

    template<class _Ty, size_t _Nx>
    struct is_array<_Ty[_Nx]> : true_type { };

    template<class _Ty>
    struct is_array<_Ty[]> : true_type { };

    template<class _Ty>
    struct is_lvalue_reference : false_type { };

    template<class _Ty>
    struct is_lvalue_reference<_Ty&> : true_type { };

    template<class _Ty>
    struct is_rvalue_reference : false_type { };

    template<class _Ty>
    struct is_rvalue_reference<_Ty&&> : true_type { };

}

#endif // ____bnb_Type_Traits_H_
