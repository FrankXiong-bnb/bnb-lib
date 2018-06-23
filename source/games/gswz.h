//=============================================================================
// gswz.h
//  														2014-8 by Frank
//=============================================================================
#ifndef ____bnb_GSWZ_H_
#define ____bnb_GSWZ_H_

#include "../games/_poker.h"

_bnb_space_in

#define poker_count 5       // 扑克张数
#define poker_max   28      // 扑克总张数

typedef enum _gswz_poker_type
{
    gpt_unknow,             // 未知
    gpt_single,             // 散牌
    gpt_double,             // 对子
    gpt_twins,              // 两对
    gpt_triple,             // 三条
    gpt_straight,           // 顺子
    gpt_flush,              // 同花
    gpt_gourd,              // 葫芦
    gpt_4same,              // 四条
    gpt_sequence,           // 同花顺
    gpt_max
} gpt_e;

//-----------------------------------------------------------------------------

struct gswzPoker : public _poker_base<gswzPoker>
{
    typedef _poker_base<gswzPoker> _BaseT_;
    explicit gswzPoker(card_t c = _invalid_card) : _poker_base(c) { }
};  // gswzPoker

typedef gswzPoker gswzp_t, poker_t, _pk_t;
typedef _pk_t::_BaseT_ _pk_base_t;

const _pk_base_t::_value_t _gc_gswz_poker_value[cn_max] = {
//none 2  3  4  5  6  7  8  9  10   J   Q   K   A  S  B
    0, 0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 0, 0
};

template<> _pk_base_t::_value_t _pk_base_t::GetCardValue() const { return (_gc_gswz_poker_value[GetNumber()]); }
template<> _pk_base_t::_value_t _pk_base_t::GetFlowerValue() const { return (GetFlower() >> 4); }
template<> _result_t _pk_base_t::Compare(const _pk_t& right) const {
    if (this->GetCardValue() < right.GetCardValue()) return (-1);
    if (right.GetCardValue() < this->GetCardValue()) return (1);

    if (this->GetFlowerValue() < right.GetFlowerValue()) return (-1);

    return (1);
}

inline bool operator <  (const _pk_t& left, const _pk_t& right) { return (left.Compare(right) < 0); }
inline bool operator >  (const _pk_t& left, const _pk_t& right) { return right < left; }
inline bool operator <= (const _pk_t& left, const _pk_t& right) { return !(right < left); }
inline bool operator >= (const _pk_t& left, const _pk_t& right) { return !(left < right); }
inline bool operator == (const _pk_t& left, const _pk_t& right) { return left.GetCardValue() == right.GetCardValue(); }
inline bool operator != (const _pk_t& left, const _pk_t& right) { return !(left == right); }

inline void Swap(_pk_t& left, _pk_t& right) {  // 交换两张扑克
    if (!left.IsIdentical(right)) left._card ^= right._card ^= left._card ^= right._card;
}

inline _result_t CompareCard(const _pk_t& left, const _pk_t& right) {  // 比较两张扑克的大小
    return left.Compare(right);
}

//-----------------------------------------------------------------------------

class gswzPokerSet : public PokerSetBase<gswzp_t, poker_count>
{
private:

    typedef PokerSetBase<gswzp_t, poker_count> _BaseT_;

    struct _info_t { _info_t() : v(0), n(0) { } _value_t v; _size_t n; };

public:

    static _result_t Compare(gpt_e le, _param_t lp, gpt_e re, _param_t rp)
    {
        if (le < re) return -1;
        if (re < le) return 1;

        gswzp_t Ll((card_t)(lp & card_mask)), Lr((card_t)(rp & card_mask));

        if (gpt_twins == le) {
            gswzp_t Hl((card_t)((lp >> 8) & card_mask)), Hr((card_t)((rp >> 8 )& card_mask));

            if (Hl.GetCardValue() < Hr.GetCardValue()) return -1;
            if (Hr.GetCardValue() < Hl.GetCardValue()) return 1;

            if (Ll.GetCardValue() < Lr.GetCardValue()) return -1;
            if (Lr.GetCardValue() < Ll.GetCardValue()) return 1;

            if (Hl.GetFlowerValue() < Hr.GetFlowerValue()) return -1;
            if (Hr.GetFlowerValue() < Hl.GetFlowerValue()) return 1; 
        }
        
        if (Ll < Lr) return -1;
        if (Lr < Ll) return 1;

        return 0;
    }

    static bool Count(_info_t (&arr)[poker_count], const gswzp_t* poker, _size_t n)
    {
        for (_index_t i = 0; i < n; ++i) {
            if (!!![](_info_t (&_arr)[poker_count], const gswzp_t& pk)->bool {
                for (_index_t i = 0; i < poker_count; ++i) {
                    if (0 == _arr[i].n) {
                        _arr[i].v = pk.GetCardValue();
                        ++_arr[i].n;
                        return true;
                    } 
                    else {
                        if (pk.GetCardValue() == _arr[i].v) {
                            ++_arr[i].n;
                            return true;
                        }
                    }
                }

                return false;
            }(arr, poker[i]))
                return false;
        }

        return true;
    }

private:

    static bool _IsSequence(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (5 != n) return false;

        gswzp_t duplicate[poker_count];
        _TraitT_::Copy(duplicate, poker_count, poker, n);        
        _TraitT_::Sort(duplicate, n);

        for (_index_t i = 1; i < n; ++i)
            if (duplicate[i-1].GetCardValue() + 1 != duplicate[i].GetCardValue()
                || duplicate[i-1].GetFlower() != duplicate[i].GetFlower())
                return false;

        if (param)
            *param = poker[_TraitT_::Limit(poker, n)].GetCard();

        return true;
    }

    static bool _IsStraight(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (5 != n) return false;

        _size_t arr[cn_max] = { 0 };
        _TraitT_::Count(arr, poker, n);

        for (_index_t i = 0; i < cn_max; ++i) {
            if (1 == arr[i]) {
                for (_index_t k = i+1; k < i+n; ++k)
                    if (1 != arr[k])
                        return false;

                if (param)
                    *param = poker[_TraitT_::Limit(poker, n)].GetCard();

                return true;
            }
        }

        return false;
    }

    static bool _IsGourd(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (5 != n) return false;

        _info_t info[2];

        for (int i = 0; i < 5; ++i) {
            if (0 == info[0].n)
                ++info[0].n, info[0].v = poker[i].GetCardValue();
            else if (poker[i].GetCardValue() == info[0].v)
                ++info[0].n;
            else if (0 == info[1].n)
                ++info[1].n, info[1].v = poker[i].GetCardValue();
            else if (poker[i].GetCardValue() == info[1].v)
                ++info[1].n;
            else
                return false;
        }

        if (3 == info[0].n) {
            if (param)
                *param = poker[_TraitT_::Limit(poker, n, info[0].v)].GetCard();
        }
        else if (3 == info[1].n) {
            if (param)
                *param = poker[_TraitT_::Limit(poker, n, info[1].v)].GetCard();
        }
        else
            return false;

        return true;
    }

    static bool _IsFlush(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (5 != n) return false; 

        for (_index_t i = 1; i < n; ++i)
            if (poker[i-1].GetFlower() != poker[i].GetFlower())
                return false;

        if (param)
            *param = poker[_TraitT_::Limit(poker, n)].GetCard();

        return true;
    }

    static bool _Is4Same(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (4 > n) return false;

        _info_t info[poker_count];
        if (!Count(info, poker, n))
            return false;
        
        for (_index_t i = 0; i < poker_count; ++i) {
            if (4 == info[i].n) {
                if (param)
                    *param = poker[_TraitT_::Limit(poker, n, info[i].v)].GetCard();

                return true;
            }
        }

        return false;
    }

    static bool _IsTriple(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (3 > n) return false;

        _info_t info[poker_count];
        if (!Count(info, poker, n))
            return false;

        for (_index_t i = 0; i < poker_count; ++i) {
            if (3 == info[i].n) {
                for (_index_t j = i+1; j < poker_count; ++j)
                    if (1 < info[j].n)
                        return false;

                if (param)
                    *param = poker[_TraitT_::Limit(poker, n, info[i].v)].GetCard();

                return true;
            }

            if (1 < info[i].n) return false;
        }

        return false; 
    }

    static bool _IsTwins(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (4 > n) return false;

        _info_t info[poker_count];
        if (!Count(info, poker, n))
            return false;

        for (_index_t i = 0; i < poker_count; ++i) {
            if (2 == info[i].n) {
                for (_index_t j = i+1; j < poker_count; ++j) {
                    if (2 == info[j].n) {                        
                        if (param) {
                            _value_t v1 = info[i].v, v2 = info[j].v;
                            if (v1 < v2 ) v1 ^= v2 ^= v1 ^= v2;

                            *param = ((poker[_TraitT_::Limit(poker, n, v1)].GetCard() << 8)
                                | (poker[_TraitT_::Limit(poker, n, v2)].GetCard() & 0xff));
                        }

                        return true;
                    }

                    if (1 < info[j].n) return false;
                }
            }

            if (1 < info[i].n) return false;
        }

        return false; 
    }

    static bool _IsDouble(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (2 > n) return false;

        _info_t info[poker_count];
        if (!Count(info, poker, n))
            return false;

        for (_index_t i = 0; i < poker_count; ++i) {
            if (2 == info[i].n) {
                for (_index_t j = i+1; j < poker_count; ++j)
                    if (1 < info[j].n)
                        return false;

                if (param)
                    *param = poker[_TraitT_::Limit(poker, n, info[i].v)].GetCard();

                return true;
            }

            if (1 < info[i].n) return false;
        }

        return false; 
    }

    static gpt_e _CheckPokerType(const gswzp_t* poker, _size_t n, _param_t* param)
    {
        if (0 == n || n > poker_count) return gpt_unknow;

        if (_IsSequence(poker, n, param)) return gpt_sequence;
                
        if (_IsStraight(poker, n, param)) return gpt_straight;
        
        if (_IsFlush(poker, n, param)) return gpt_flush;
        
        if (_IsGourd(poker, n, param)) return gpt_gourd;

        if (_Is4Same(poker, n, param)) return gpt_4same;

        if (_IsTwins(poker, n, param)) return gpt_twins;

        if (_IsTriple(poker, n, param)) return gpt_triple;

        if (_IsDouble(poker, n, param)) return gpt_double;
        
        if (param)
            *param = poker[_TraitT_::Limit(poker, n)].GetCard();

        return gpt_single;
    }

public:

    gpt_e CheckTypeForPublic(_param_t* param = nullptr) const
    {
        if (0 == _size) return gpt_unknow;

        return _CheckPokerType(_poker+1, _size-1, param);
    }

    gpt_e CheckTypeForWhole(_param_t* param = nullptr) const
    {
        return _CheckPokerType(_poker, _size, param);
    }

    gswzPokerSet() : _BaseT_() { }
    gswzPokerSet(const _PkT_* pSet, _size_t n) : _BaseT_(pSet, n) { }

};

//-----------------------------------------------------------------------------

const gswzp_t _gc_gswz_poker_pool[poker_max] = {
    gswzp_t(cf_T | cn_8), gswzp_t(cf_X | cn_8), gswzp_t(cf_M | cn_8), gswzp_t(cf_F | cn_8),
    gswzp_t(cf_T | cn_9), gswzp_t(cf_X | cn_9), gswzp_t(cf_M | cn_9), gswzp_t(cf_F | cn_9),
    gswzp_t(cf_T | cn_T), gswzp_t(cf_X | cn_T), gswzp_t(cf_M | cn_T), gswzp_t(cf_F | cn_T),
    gswzp_t(cf_T | cn_J), gswzp_t(cf_X | cn_J), gswzp_t(cf_M | cn_J), gswzp_t(cf_F | cn_J),
    gswzp_t(cf_T | cn_Q), gswzp_t(cf_X | cn_Q), gswzp_t(cf_M | cn_Q), gswzp_t(cf_F | cn_Q),
    gswzp_t(cf_T | cn_K), gswzp_t(cf_X | cn_K), gswzp_t(cf_M | cn_K), gswzp_t(cf_F | cn_K),
    gswzp_t(cf_T | cn_A), gswzp_t(cf_X | cn_A), gswzp_t(cf_M | cn_A), gswzp_t(cf_F | cn_A)
};

typedef PokerPool<gswzp_t, poker_max> gswzPokerPool;

template<> void gswzPokerPool::_InitializePoker()
{
    for (_index_t i = 0; i < poker_max; ++i)
        _pool[i] = _gc_gswz_poker_pool[i];
}

_bnb_space_out

#endif