//=============================================================================
// wxhh.h
//
// Exception :
//      
//
//=============================================================================
#ifndef ____bnb_WXHH_H_
#define ____bnb_WXHH_H_

#include "../games/_poker.h"

_bnb_space_in

struct wxhhPoker : public _poker_base<wxhhPoker>
{
    typedef _poker_base<wxhhPoker> _BaseT_;

    explicit wxhhPoker(card_t c = _invalid_card) : _BaseT_(c) { }
};

typedef wxhhPoker wxhhp_t, poker_t, _pk_t;
typedef _pk_t::_BaseT_ _pk_base_t;

const _pk_base_t::_value_t _gc_wxhh_poker_value[cn_max] = {
// none 2  3  4  5  6  7  8  9  10  J   Q   K  A   S   B
    15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 13, 14
};

template<> _pk_base_t::_value_t _pk_base_t::GetCardValue() const { return (_gc_wxhh_poker_value[GetNumber()]); }
template<> _pk_base_t::_value_t _pk_base_t::GetFlowerValue() const { return (GetFlower() >> 4); }

bool operator <  (const wxhhp_t& left, const wxhhp_t& right) { return (left.Compare(right) < 0); }
bool operator >  (const wxhhp_t& left, const wxhhp_t& right) { return right < left; }
bool operator <= (const wxhhp_t& left, const wxhhp_t& right) { return !(right < left); }
bool operator >= (const wxhhp_t& left, const wxhhp_t& right) { return !(left < right); }
bool operator == (const wxhhp_t& left, const wxhhp_t& right) { return !(left < right) && !(right < left); }
bool operator != (const wxhhp_t& left, const wxhhp_t& right) { return !(left == right); }

void _SwapCard(wxhhp_t& left, wxhhp_t& right) {
    if (!left.IsIdentical(right)) left._card ^= right._card ^= left._card ^= right._card;
}

#define poker_max       54

typedef wxhhp_t pk_t;
typedef pk_t    poker_t;

const pk_t _gc_wxhh_pk_pool[poker_max] = {
    pk_t(cf_F | cn_2), pk_t(cf_M | cn_2), pk_t(cf_X | cn_2), pk_t(cf_T | cn_2),
    pk_t(cf_F | cn_3), pk_t(cf_M | cn_3), pk_t(cf_X | cn_3), pk_t(cf_T | cn_3),
    pk_t(cf_F | cn_4), pk_t(cf_M | cn_4), pk_t(cf_X | cn_4), pk_t(cf_T | cn_4),
    pk_t(cf_F | cn_5), pk_t(cf_M | cn_5), pk_t(cf_X | cn_5), pk_t(cf_T | cn_5),
    pk_t(cf_F | cn_6), pk_t(cf_M | cn_6), pk_t(cf_X | cn_6), pk_t(cf_T | cn_6),
    pk_t(cf_F | cn_7), pk_t(cf_M | cn_7), pk_t(cf_X | cn_7), pk_t(cf_T | cn_7),
    pk_t(cf_F | cn_8), pk_t(cf_M | cn_8), pk_t(cf_X | cn_8), pk_t(cf_T | cn_8),
    pk_t(cf_F | cn_9), pk_t(cf_M | cn_9), pk_t(cf_X | cn_9), pk_t(cf_T | cn_9),
    pk_t(cf_F | cn_T), pk_t(cf_M | cn_T), pk_t(cf_X | cn_T), pk_t(cf_T | cn_T),
    pk_t(cf_F | cn_J), pk_t(cf_M | cn_J), pk_t(cf_X | cn_J), pk_t(cf_T | cn_J),
    pk_t(cf_F | cn_Q), pk_t(cf_M | cn_Q), pk_t(cf_X | cn_Q), pk_t(cf_T | cn_Q),
    pk_t(cf_F | cn_K), pk_t(cf_M | cn_K), pk_t(cf_X | cn_K), pk_t(cf_T | cn_K),
    pk_t(cf_F | cn_A), pk_t(cf_M | cn_A), pk_t(cf_X | cn_A), pk_t(cf_T | cn_A),
    pk_t(cf_K | cn_S), pk_t(cf_K | cn_B)
};

_bnb_space_out

#endif
//                                                         2014-10 by Frank
//-----------------------------------------------------------------------------