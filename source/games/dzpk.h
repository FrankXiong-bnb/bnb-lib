//=============================================================================
// dzpk.h
//
// Exception :
//      定义德州扑克类，以及相关牌型判断和比较逻辑算法，基于纯C++实现。
//
//=============================================================================
#ifndef ____bnb_DZPK_H_
#define ____bnb_DZPK_H_

#include "..\games\_poker.h"

_bnb_space_in

// 定义相关数据
//-----------------------------------------------------------------------------

#define count_fkind     4   // 花色种类数
#define count_poker     52  // 扑克池张数
#define count_need      5   // 需要的张数
#define count_public    5   // 公共牌张数
#define count_bluff     2   // 底牌张数
#define count_allpk     (count_bluff + count_public)

// 定义牌型枚举
//-----------------------------------------------------------------------------

typedef enum _dz_poker_type
{
    dpt_unknow,             // 未知
    dpt_single,             // 散牌
    dpt_double,             // 对子
    dpt_twins,              // 两对
    dpt_triple,             // 三条
    dpt_straight,           // 顺子
    dpt_flush,              // 同花
    dpt_gourd,              // 葫芦
    dpt_4same,              // 四条
    dpt_sequence,           // 同花顺
    dpt_royalseq,           // 皇家同花顺
    dpt_max
} dpt_e;

// 定义德州扑克类
//-----------------------------------------------------------------------------

struct dzPoker : public _poker_base<dzPoker>
{
    typedef _poker_base<dzPoker> _BaseT_;
    explicit dzPoker(card_t c = _invalid_card) : _BaseT_(c) { }
};  // struct dzPoker

typedef dzPoker poker_t, _pk_t;
typedef _pk_t::_BaseT_ _pk_base_t;

// 牌值定义
//-----------------------------------------------------------------------------

const _pk_base_t::_value_t _gc_dz_poker_value[cn_max] = {
//none 2  3  4  5  6  7  8  9  10   J   Q   K   A  S  B
    0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 0
};

// 特例化操作改写
//-----------------------------------------------------------------------------

template<> _pk_base_t::_value_t _pk_base_t::GetCardValue() const { return (_gc_dz_poker_value[GetNumber()]); }
template<> _pk_base_t::_value_t _pk_base_t::GetFlowerValue() const { return (GetFlower() >> 4); }

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

// 扑克参数结构(基于不同的牌型可能需要不同的参数)
//-----------------------------------------------------------------------------

typedef union _dz_param_t {

    card_t _c[5];

    union { card_t _a[1]; struct { card_t _c1; } _s; } _1p;
    union { card_t _a[2]; struct { card_t _c1, _c2; } _s; } _2p;
    union { card_t _a[3]; struct { card_t _c1, _c2, _c3; } _s; } _3p;
    union { card_t _a[4]; struct { card_t _c1, _c2, _c3, _c4; } _s; } _4p;
    union { card_t _a[5]; struct { card_t _c1, _c2, _c3, _c4, _c5; } _s; } _5p;

} dzparam_t;    // union _dz_param_t

template<_size_t _np>
_result_t _compare_param_for_same_type(const dzparam_t& left, const dzparam_t& right) {
    static_assert(_np > 0 && _np <= count_need, "The count of param must be between 1 and count_need");

    for (_index_t i = 0; i < _np; ++i)
        if (_result_t rt = CompareCard(_pk_t(left._c[i]), _pk_t(right._c[i])))
            return rt;

    return 0;
}

template<> _result_t _compare_param_for_same_type<5>(const dzparam_t& left, const dzparam_t& right) {
    for (_index_t i = 0; i < 5; ++i)
        if (_result_t rt = CompareCard(_pk_t(left._5p._a[i]), _pk_t(right._5p._a[i])))
            return rt;

    return 0;
}

template<> _result_t _compare_param_for_same_type<4>(const dzparam_t& left, const dzparam_t& right) {
    for (_index_t i = 0; i < 4; ++i)
        if (_result_t rt = CompareCard(_pk_t(left._4p._a[i]), _pk_t(right._4p._a[i])))
            return rt;

    return 0;
}

template<> _result_t _compare_param_for_same_type<3>(const dzparam_t& left, const dzparam_t& right) {
    for (_index_t i = 0; i < 3; ++i)
        if (_result_t rt = CompareCard(_pk_t(left._3p._a[i]), _pk_t(right._3p._a[i])))
            return rt;

    return 0;
}

template<> _result_t _compare_param_for_same_type<2>(const dzparam_t& left, const dzparam_t& right) {
    for (_index_t i = 0; i < 2; ++i)
        if (_result_t rt = CompareCard(_pk_t(left._2p._a[i]), _pk_t(right._2p._a[i])))
            return rt;

    return 0;
}

template<> _result_t _compare_param_for_same_type<1>(const dzparam_t& left, const dzparam_t& right) {
    return CompareCard(_pk_t(left._1p._s._c1), _pk_t(right._1p._s._c1));
}

// 牌型信息结构
//-----------------------------------------------------------------------------

typedef struct _dz_info_t {

    _dz_info_t() { Clear(); }
    void Clear() { _dzpt = dpt_unknow; for (int i = 0; i < 5; _param._c[i++] = 0); }

    dpt_e       _dzpt;      // 牌型
    dzparam_t   _param;     // 参数

} dzinfo_t; // class _dz_info_t

_result_t CompareType(const _dz_info_t& left, const _dz_info_t& right) {
    if (left._dzpt < right._dzpt) return (-1);
    if (right._dzpt < left._dzpt) return (1);

    switch (left._dzpt)
    {
    case dpt_flush:         // 比较同花和高牌需要5个参数
    case dpt_single:
        return _compare_param_for_same_type<5>(left._param, right._param);

    case dpt_double:        // 比较对子需要4个参数
        return _compare_param_for_same_type<4>(left._param, right._param);

    case dpt_twins:         // 比较两对和三条需要3个参数
    case dpt_triple:
        return _compare_param_for_same_type<3>(left._param, right._param);

    case dpt_gourd:         // 比较葫芦和四条需要2个参数
    case dpt_4same:
        return _compare_param_for_same_type<2>(left._param, right._param);

    case dpt_royalseq:      // 比较顺子系列需要1个参数
    case dpt_sequence:
    case dpt_straight:
        return _compare_param_for_same_type<1>(left._param, right._param);

    default:
        return (0);
    }
}

// 扑克索引结构
//-----------------------------------------------------------------------------

typedef class _pk_pos_t
{
public:

    _pk_pos_t() : _pos(0) { }

    const _index_t& GetPos() const { return _pos; }
    const _pk_t& GetPoker() const { return _pk; }

    void SetPoker(const _pk_t& pk) { _pk = pk; }
    void SetPos(const _index_t& i) { _pos = i; }

    bool LessThan(const _pk_pos_t& right) const { return _pk < right._pk; }
    void Swap(_pk_pos_t& right) {
        if (this != &right) {
            _bnb Swap(_pk, right._pk);
            _pos ^= right._pos ^= _pos ^= right._pos;
        }
    }

protected:

    _pk_t       _pk;    // 牌数据
    _index_t    _pos;   // 牌索引

} pkpos_t;  // class _pk_pos_t

inline bool operator < (const pkpos_t& left, const pkpos_t& right) { return left.LessThan(right); }
inline void Swap(pkpos_t& left, pkpos_t& right) { left.Swap(right); }
inline void Sort(pkpos_t* pkpos, _size_t n) {    
    for (_index_t minpos(0), _index(0); n > 0; minpos = 0) {
        for (_index = 1; _index < n; ++_index)
            if (pkpos[_index] < pkpos[minpos])
                minpos = _index;

        Swap(pkpos[--n], pkpos[minpos]);
    }
}

// 个性化划分扑克
//-----------------------------------------------------------------------------

template<_size_t _nmax>
class _pk_trait_set
{
    static_assert(_nmax > 0, "The template parameter _nmax must be greater than 0.");

public:

    static _size_t GetMaxSize() {  return _nmax; }

    _pk_trait_set() : _n(0) { }

    _size_t GetSize() const { return _n; }

    pkpos_t& operator [] (const _index_t& n) { return _pkpos[n]; }
    const pkpos_t& operator [] (const _index_t& n) const { return _pkpos[n]; }

    bool Add(const _pk_t& pk, const _index_t& i) {   // 在 i 位置添加一张扑克
        if (_n < _nmax) {
            _pkpos[_n].SetPoker(pk);
            _pkpos[_n].SetPos(i);
            ++_n;

            return true;
        }

        return false;
    }

    bool Add(const pkpos_t& pkp) { return Add(pkp.GetPoker(), pkp.GetPos()); }

    void Clear() {
        for (_index_t i = 0; i < _nmax; ++i) {
            _pkpos[i].SetPoker(_pk_t());
            _pkpos[i].SetPos(0);
        }

        _n = 0;
    }

protected:

    pkpos_t _pkpos[_nmax];  // 扑克数据集
    _size_t _n;             // 数量

};  // class _pk_trait_set

// 按点数划分扑克
//-----------------------------------------------------------------------------

class _same_number_t : public _pk_trait_set<count_fkind>
{
public:

    bool AsFlower(const _same_number_t& sn) const {
        for (_index_t i = 0; i < _n; ++i)
            for (_index_t j = 0; j < sn._n; ++j)
                if (_pkpos[i].GetPoker().GetFlower() == sn[j].GetPoker().GetFlower())
                    return true;

        return false;
    }

};  // class _same_number_t

// 按花色划分扑克
//-----------------------------------------------------------------------------

class _same_flower_t : public _pk_trait_set<count_allpk>
{
public:

    void Sort() { _bnb Sort(_pkpos, _n); }

};  // class _same_flower_t

//  扑克容器
//-----------------------------------------------------------------------------

template<typename _SetT, _size_t _nmax>
class _dzpk_container
{
public:
    
    static _size_t Capacity() { return _nmax; }

    _dzpk_container() { }
    _dzpk_container(const _pk_t* poker, _size_t n) {
        for (_index_t i = 0; i < n; ++i)
            Add(poker[i], i);
    }

    _SetT& operator [] (const _index_t& n) { return _pkn[n]; }
    const _SetT& operator [] (const _index_t& n) const { return _pkn[n]; }

    // 需要改写，这将决定按不同方式划分扑克的时候的分类规则。
    bool Add(const _pk_t& pk, _index_t i) { return false; }

    bool Add(const pkpos_t& pkp) { return Add(pkp.GetPoker(), pkp.GetPos()); }

    void Assign(const _pk_t* poker, _size_t n) {
        Clear();

        for (_index_t i = 0; i < n; ++i)
            Add(poker[i], i);
    }

    void Clear() {
        for (_index_t i = 0; i < _nmax; ++i)
            _pkn[i].Clear();
    }

private:

    _SetT _pkn[_nmax];

};  // class _dzpk_container

// 扑克容器：按点数划分存贮牌数组
//-----------------------------------------------------------------------------

typedef _dzpk_container<_same_number_t, cn_max> _dzpk_container_by_number;

template<> bool _dzpk_container_by_number::Add(const _pk_t& pk, _index_t i) {
    return _pkn[pk.GetNumber()].Add(pk, i);
}

// 扑克容器：按花色划分存贮牌数组
//-----------------------------------------------------------------------------
typedef _dzpk_container<_same_flower_t, count_fkind> _dzpk_container_by_flower;

template<> bool _dzpk_container_by_flower::Add(const _pk_t& pk, _index_t i) {
    return _pkn[pk.GetFlowerValue()].Add(pk, i);
}

// 针对德州扑克7选5设计的简单组合函数(备用)
//-----------------------------------------------------------------------------

template<typename _FuncT>
static inline _size_t Combination(_FuncT pFunc)
{
    const _index_t _Except(count_allpk - count_need);
    _index_t _Pos = 0, _Top = 0, _Stack[_Except] = { 0 };

    _size_t _Count = 0;

    do {
        _Stack[_Top++] = _Pos;

        for ( ; _Top == _Except; ++_Count) {
            pFunc(_Stack);

            for (_Pos = count_allpk; _Pos >= (count_need + _Top) && _Top; ) {
                _Pos = _Stack[--_Top] + 1;

                if (_Pos <= (count_need + _Top)) {
                    _Stack[_Top++] = _Pos;
                    break;
                }
            }
        }

        ++_Pos;
    } while (_Top);

    return _Count;
}

// 德州扑克个性化操作
//-----------------------------------------------------------------------------

class dzpk_trait
{
private:

    typedef _dzpk_container_by_number dz_ncon_t;
    typedef _dzpk_container_by_flower dz_fcon_t;

    // 判定同花顺
    static bool _IsSequence(const _pk_t* poker, _size_t n, byte_t* index, dzparam_t* param) {
        dz_fcon_t dzcon(poker, n);

        for (_index_t i = 0; i < count_fkind; ++i) {
            if (dzcon[i].GetSize() >= count_need) {

                dz_ncon_t dzn;
                for (_index_t k = 0; k < dzcon[i].GetSize(); ++k)
                    dzn.Add(dzcon[i][k]);
                
                return _IsStraight(dzn, index, param);
            }
        }

        return false;
    }

    // 判定特殊的顺子
    static bool _IsSpecialStraight(const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        if (dzcon[cn_A].GetSize() == 0)
            return false;

        for (_index_t i = cn_5; i > cn_unknow; --i)
            if (dzcon[i].GetSize() == 0)
                return false;

        if (index) {
            *index |= (1 << dzcon[cn_A][0].GetPos());
            for (_index_t i = cn_5; i > cn_unknow; --i)
                *index |= (1 << dzcon[i][0].GetPos());
        }

        if (param)
            param->_1p._s._c1 = dzcon[cn_5][0].GetPoker().GetCard();

        return true;
    }

    // 判定顺子
    static bool _IsStraight(const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        for (_index_t i = dz_ncon_t::Capacity() - 1; i > 0; --i) {
            if (i < cn_6) break;

            if (dzcon[i].GetSize() > 0) {
                if ([&dzcon](const _index_t& start)->bool {
                        for (_index_t i = start - 1; i > start - count_need; --i)
                            if (dzcon[i].GetSize() == 0)
                                return false;

                        return true;
                    }(i)
                   )
                {
                    if (index)
                        for (_index_t start = i; start > i - count_need; --start)
                            *index |= (1 << dzcon[start][0].GetPos());

                    if (param)
                        param->_1p._s._c1 = dzcon[i][0].GetPoker().GetCard();

                    return true;
                }
            }
        }

        return (_IsSpecialStraight(dzcon, index, param));
    }

    static bool _IsStraight(const _pk_t* poker, _size_t n, byte_t* index, dzparam_t* param) {
        return _IsStraight(dz_ncon_t(poker, n), index, param);
    }

    // 判定同花
    static bool _IsFlush(const _pk_t* poker, _size_t n, byte_t* index, dzparam_t* param) {
        dz_fcon_t dzcon(poker, n);

        for (_index_t i = 0; i < count_fkind; ++i) {
            if (dzcon[i].GetSize() >= count_need) {
                dzcon[i].Sort();

                if (index)
                    for (_index_t j = 0; j < count_need; ++j)
                        *index |= (1 << dzcon[i][j].GetPos());

                if (param)
                    for (_index_t j = 0; j < count_need; ++j)
                        param->_5p._a[j] = dzcon[i][j].GetPoker().GetCard();

                return true;
            }
        }

        return false;
    }

    /*
     *	_CheckTypeFor_X 系列函数将根据按点数划分扑克后数量最多的扑克参数判定牌型
     *  如果相同点数扑克的最多数量是4张，则可能被判定为四条。
     *  相同点数最多的数量是3张，则可能是三条或葫芦
     *  相同点数最多的数量是2张，则可能是一对或两对
     *  相同点数最多的数量是1张，则可能是高牌
     */
    static dpt_e _CheckTypeFor_4(const _index_t& first, const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        for (_index_t second = dz_ncon_t::Capacity()-1; second > 0; --second) {
            if (second != first && dzcon[second].GetSize() > 0) {
                if (index) {
                    _index_t x = dzcon[second][0].GetPos();

                    *index |= (1 << dzcon[second][0].GetPos());

                    for (_index_t j = 0; j < 4; ++j)
                        *index |= (1 << dzcon[first][j].GetPos());
                }

                if (param) {
                    param->_2p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                    param->_2p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                }

                return dpt_4same;
            }
        }

        return dpt_unknow;
    }

    static dpt_e _CheckTypeFor_3(const _index_t& first, const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        _index_t second = 0;

        for (_index_t i = dz_ncon_t::Capacity()-1; i > 0; --i)
            if (i != first && dzcon[i].GetSize() > dzcon[second].GetSize())
                if (dzcon[second = i].GetSize() > 1)
                    break;

        if (second > 0 && dzcon[second].GetSize() > 0) {
            if (dzcon[second].GetSize() == 1) {
                for (_index_t third = second - 1; third > 0; --third) {
                    if (third != first && dzcon[third].GetSize() > 0) {
                        if (index) {
                            *index |= (1 << dzcon[second][0].GetPos());
                            *index |= (1 << dzcon[third][0].GetPos());

                            for (_index_t j = 0; j < 3; ++j)
                                *index |= (1 << dzcon[first][j].GetPos());
                        }

                        if (param) {
                            param->_3p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                            param->_3p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                            param->_3p._s._c3 = dzcon[third][0].GetPoker().GetCard();
                        }

                        return dpt_triple;
                    }
                }
            }
            else {
                if (index) {
                    for (_index_t j = 0; j < 3; ++j)
                        *index |= (1 << dzcon[first][j].GetPos());

                    for (_index_t j = 0; j < 2; ++j)
                        *index |= (1 << dzcon[second][j].GetPos());
                }

                if (param) {
                    param->_2p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                    param->_2p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                }

                return dpt_gourd;
            }
        }

        return dpt_unknow;
    }

    static dpt_e _CheckTypeFor_2(const _index_t& first, const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        _index_t second = 0;

        for (_index_t i = dz_ncon_t::Capacity()-1; i > 0; --i)
            if (i != first && dzcon[i].GetSize() > dzcon[second].GetSize())
                if (dzcon[second = i].GetSize() > 1)
                    break;

        if (second > 0 && dzcon[second].GetSize() > 0) {
            if (dzcon[second].GetSize() == 1) {
                for (_index_t third = second - 1; third > 0; --third) {
                    if (third != first && dzcon[third].GetSize() > 0) {
                        for (_index_t fouth = third - 1; fouth > 0; --fouth) {
                            if (fouth != first && dzcon[fouth].GetSize() > 0) {
                                if (index) {
                                    *index |= (1 << dzcon[second][0].GetPos());
                                    *index |= (1 << dzcon[third][0].GetPos());
                                    *index |= (1 << dzcon[fouth][0].GetPos());

                                    for (_index_t j = 0; j < 2; ++j)
                                        *index |= (1 << dzcon[first][j].GetPos());
                                }

                                if (param) {
                                    param->_4p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                                    param->_4p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                                    param->_4p._s._c3 = dzcon[third][0].GetPoker().GetCard();
                                    param->_4p._s._c4 = dzcon[fouth][0].GetPoker().GetCard();
                                }

                                return dpt_double;
                            }
                        }
                    }
                }
            }
            else {
                for (_index_t third = dz_ncon_t::Capacity() - 1; third > 0; --third) {
                    if (third != first && third != second && dzcon[third].GetSize() > 0) {
                        if (index) {
                            *index |= (1 << dzcon[third][0].GetPos());

                            for (_index_t j = 0; j < 2; ++j) {
                                *index |= (1 << dzcon[first][j].GetPos());
                                *index |= (1 << dzcon[second][j].GetPos());
                            }
                        }

                        if (param) {
                            param->_3p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                            param->_3p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                            param->_3p._s._c3 = dzcon[third][0].GetPoker().GetCard();
                        }

                        return dpt_twins;
                    }
                }
            }
        }

        return dpt_unknow;
    }

    static dpt_e _CheckTypeFor_1(const _index_t& first, const dz_ncon_t& dzcon, byte_t* index, dzparam_t* param) {
        for (_index_t second = first - 1; second > 0; --second) {
            if (dzcon[second].GetSize() > 0) {
                for (_index_t third = second - 1; third > 0; --third) {
                    if (dzcon[third].GetSize() > 0) {
                        for (_index_t fouth = third - 1; fouth > 0; --fouth) {
                            if (dzcon[fouth].GetSize() > 0) {
                                for (_index_t fifth = fouth - 1; fifth > 0; --fifth) {
                                    if (dzcon[fifth].GetSize() > 0) {
                                        if (index) {
                                            *index |= (1 << dzcon[first][0].GetPos());
                                            *index |= (1 << dzcon[second][0].GetPos());
                                            *index |= (1 << dzcon[third][0].GetPos());
                                            *index |= (1 << dzcon[fouth][0].GetPos());
                                            *index |= (1 << dzcon[fifth][0].GetPos());
                                        }

                                        if (param) {
                                            param->_5p._s._c1 = dzcon[first][0].GetPoker().GetCard();
                                            param->_5p._s._c2 = dzcon[second][0].GetPoker().GetCard();
                                            param->_5p._s._c3 = dzcon[third][0].GetPoker().GetCard();
                                            param->_5p._s._c4 = dzcon[fouth][0].GetPoker().GetCard();
                                            param->_5p._s._c5 = dzcon[fifth][0].GetPoker().GetCard();
                                        }

                                        return dpt_single;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return dpt_unknow;
    }

public:

    static dpt_e HintType(const _pk_t* poker, _size_t n, byte_t& index) {
        dzparam_t param = { 0 };
        if (_IsSequence(poker, n, &index, &param))
            return (cn_A == _pk_t(param._1p._s._c1).GetNumber() ? dpt_royalseq : dpt_sequence);

        if (_IsFlush(poker, n, &index, nullptr))    return dpt_flush;
        if (_IsStraight(poker, n, &index, nullptr)) return dpt_straight;

        dz_ncon_t dzcon(poker, n);
        _index_t first = 0; // first 表示相同点数最多的牌，代表牌型的第一个参数。

        for (_index_t i = dz_ncon_t::Capacity() - 1; i > 0; --i)
            if (dzcon[i].GetSize() > dzcon[first].GetSize())
                first = i;

        if (0 < first && 0 < dzcon[first].GetSize()) {          // 如果找到第一多的位置
            if (1 < dzcon[first].GetSize()){                    // 如果第一多的牌数量大于1                                                
                for (_index_t i = 0; i < dzcon[first].GetSize(); ++i)
                    index |= (1 << dzcon[first][i].GetPos());   // 将第一多位置的牌索引保存

                if (4 == dzcon[first].GetSize())
                    return dpt_4same;       // 如果第一多的牌数量是4，直接是4条。

                _index_t second = 0;        // 找到牌型第二多且大于1的牌位置
                for (_index_t i = dz_ncon_t::Capacity()-1; i > 0; --i)
                    if (i != first && dzcon[i].GetSize() > dzcon[second].GetSize())
                        if (dzcon[second = i].GetSize() > 1)
                            break;

                if (1 < dzcon[first].GetSize()) {
                    if (0 < second && 1 < dzcon[second].GetSize()) {
                        index |= (1 << dzcon[second][0].GetPos());
                        index |= (1 << dzcon[second][1].GetPos());

                        if (3 == dzcon[first].GetSize())
                            return dpt_gourd;
                        else
                            return dpt_twins;
                    }

                    if (3 == dzcon[first].GetSize())
                        return dpt_triple;
                    else
                        return dpt_double;
                }
            }

            return dpt_single;  // 第一多的牌数量是1的话是高牌
        }

        return dpt_unknow;
    }

    static dpt_e CheckType(const _pk_t* poker, _size_t n, byte_t* index, dzparam_t* param) {
        dzparam_t p;
        if (_IsSequence(poker, n, index, &p)){
            if (param) *param = p;
            return (cn_A == _pk_t(p._1p._s._c1).GetNumber() ? dpt_royalseq : dpt_sequence);
        }

        if (_IsFlush(poker, n, index, param))    return dpt_flush;
        if (_IsStraight(poker, n, index, param)) return dpt_straight;

        dz_ncon_t dzcon(poker, n);
        _index_t first = 0; // first 表示相同点数最多的牌，代表牌型的第一个参数。

        for (_index_t i = dz_ncon_t::Capacity() - 1; i > 0; --i)
            if (dzcon[i].GetSize() > dzcon[first].GetSize())
                first = i;

        switch (dzcon[first].GetSize()) // 相同点数的牌数量可能是1/2/3/4张
        {                               // 根据相同的张数对剩下的牌再次进行筛选
        case 4:
            return _CheckTypeFor_4(first, dzcon, index, param);
        case 3:
            return _CheckTypeFor_3(first, dzcon, index, param);
        case 2:
            return _CheckTypeFor_2(first, dzcon, index, param);
        case 1:
            return _CheckTypeFor_1(first, dzcon, index, param);
        default:
            return dpt_unknow;
        }
    }

    static _result_t CompareSet(const _pk_t* left, const _pk_t* right, _size_t n) {
        dzinfo_t lp, rp;

        lp._dzpt = CheckType(left, n, nullptr, &lp._param);
        rp._dzpt = CheckType(right, n, nullptr, &rp._param);

        return CompareType(lp, rp);
    }
};  // class dzpk_trait

class PublicSet;

// 底牌类型
//-----------------------------------------------------------------------------

class BluffSet : public PokerSetBase<_pk_t, count_bluff>
{
    typedef PublicSet public_t;
    typedef BluffSet bluff_t;

public:

    dpt_e CheckType(const public_t& pub, byte_t* index, dzparam_t* param) const;
    _result_t ComparePoker(const bluff_t& right, const public_t& pub) const;
    
};  // class BluffSet

// 公共牌类型
//-----------------------------------------------------------------------------

class PublicSet : public PokerSetBase<_pk_t, count_public>
{
    typedef PublicSet public_t;
    typedef BluffSet bluff_t;

public:

    dpt_e CheckType(const bluff_t& bluff, byte_t* index, dzparam_t* param) const;
    _result_t ComparePoker(const bluff_t& left, const bluff_t& right) const;

};  // class PublicSet

//-----------------------------------------------------------------------------

inline dpt_e BluffSet::CheckType(const public_t& pub, byte_t* index, dzparam_t* param) const {
    _size_t n = 0;
    _pk_t pkset[count_allpk];

    for (_index_t i = 0; i < _size; pkset[n++] = _poker[i++]);
    for (_index_t i = 0; i < pub.GetSize(); pkset[n++] = pub[i++]);

    return dzpk_trait::CheckType(pkset, n, index, param);
}

inline _result_t BluffSet::ComparePoker(const bluff_t& right, const public_t& pub) const {
    if (_size != right.GetSize()) return (-1);

    _size_t n = 0;
    _pk_t pkleft[count_allpk], pkright[count_allpk];

    for (_index_t i = 0; i < _size; ++i, ++n) {
        pkleft[n] = _poker[i];
        pkright[n] = right._poker[i];
    }

    for (_index_t i = 0; i < pub.GetSize(); ++i, ++n) {
        pkleft[n] = pub[i];
        pkright[n] = pub[i];
    }

    return dzpk_trait::CompareSet(pkleft, pkright, n);
}

inline dpt_e PublicSet::CheckType(const bluff_t& bluff, byte_t* index, dzparam_t* param) const {
    _size_t n = 0;
    _pk_t pkset[count_allpk];

    for (_index_t i = 0; i < bluff.GetSize(); pkset[n++] = bluff[i++]);
    for (_index_t i = 0; i < _size; pkset[n++] = _poker[i++]);

    return dzpk_trait::CheckType(pkset, n, index, param);
}

inline _result_t PublicSet::ComparePoker(const bluff_t& left, const bluff_t& right) const {
    if (left.GetSize() != right.GetSize()) return (-1);

    _size_t n = 0;
    _pk_t pkleft[count_allpk], pkright[count_allpk];

    for (_index_t i = 0; i < left.GetSize(); ++i, ++n) {
        pkleft[n] = left[i];
        pkright[n] = right[i];
    }

    for (_index_t i = 0; i < _size; ++i, ++n) {
        pkleft[n] = _poker[i];
        pkright[n] = _poker[i];
    }

    return dzpk_trait::CompareSet(pkleft, pkright, n);
}

//-----------------------------------------------------------------------------

inline dpt_e HintType(const BluffSet& bluff, const PublicSet& pub, byte_t& index) {
    _size_t n = 0;
    _pk_t pkset[count_allpk];

    for (_index_t i = 0; i < bluff.GetSize(); pkset[n++] = bluff[i++]);
    for (_index_t i = 0; i < pub.GetSize(); pkset[n++] = pub[i++]);

    return dzpk_trait::HintType(pkset, n, index);
}

//-----------------------------------------------------------------------------

inline dpt_e CheckType(const BluffSet& bluff, const PublicSet& pub, byte_t* index, dzparam_t* param) {
    _size_t n = 0;
    _pk_t pkset[count_allpk];

    for (_index_t i = 0; i < bluff.GetSize(); pkset[n++] = bluff[i++]);
    for (_index_t i = 0; i < pub.GetSize(); pkset[n++] = pub[i++]);

    return dzpk_trait::CheckType(pkset, n, index, param);
}

//-----------------------------------------------------------------------------

inline _result_t ComparePoker(const BluffSet& left, const BluffSet& right, const PublicSet& pub) {
    if (left.GetSize() != right.GetSize()) return (-1);

    _size_t n = 0;
    _pk_t pkleft[count_allpk], pkright[count_allpk];

    for (_index_t i = 0; i < left.GetSize(); ++i, ++n) {
        pkleft[n] = left[i];
        pkright[n] = right[i];
    }

    for (_index_t i = 0; i < pub.GetSize(); ++i, ++n) {
        pkleft[n] = pub[i];
        pkright[n] = pub[i];
    }

    return dzpk_trait::CompareSet(pkleft, pkright, n);
}

// 德州扑克池
//-----------------------------------------------------------------------------

const _pk_t _gc_dz_poker_pool[count_poker] = {
    _pk_t(cf_T | cn_2), _pk_t(cf_X | cn_2), _pk_t(cf_M | cn_2), _pk_t(cf_F | cn_2),
    _pk_t(cf_T | cn_3), _pk_t(cf_X | cn_3), _pk_t(cf_M | cn_3), _pk_t(cf_F | cn_3),
    _pk_t(cf_T | cn_4), _pk_t(cf_X | cn_4), _pk_t(cf_M | cn_4), _pk_t(cf_F | cn_4),
    _pk_t(cf_T | cn_5), _pk_t(cf_X | cn_5), _pk_t(cf_M | cn_5), _pk_t(cf_F | cn_5),
    _pk_t(cf_T | cn_6), _pk_t(cf_X | cn_6), _pk_t(cf_M | cn_6), _pk_t(cf_F | cn_6),
    _pk_t(cf_T | cn_7), _pk_t(cf_X | cn_7), _pk_t(cf_M | cn_7), _pk_t(cf_F | cn_7),
    _pk_t(cf_T | cn_8), _pk_t(cf_X | cn_8), _pk_t(cf_M | cn_8), _pk_t(cf_F | cn_8),
    _pk_t(cf_T | cn_9), _pk_t(cf_X | cn_9), _pk_t(cf_M | cn_9), _pk_t(cf_F | cn_9),
    _pk_t(cf_T | cn_T), _pk_t(cf_X | cn_T), _pk_t(cf_M | cn_T), _pk_t(cf_F | cn_T),
    _pk_t(cf_T | cn_J), _pk_t(cf_X | cn_J), _pk_t(cf_M | cn_J), _pk_t(cf_F | cn_J),
    _pk_t(cf_T | cn_Q), _pk_t(cf_X | cn_Q), _pk_t(cf_M | cn_Q), _pk_t(cf_F | cn_Q),
    _pk_t(cf_T | cn_K), _pk_t(cf_X | cn_K), _pk_t(cf_M | cn_K), _pk_t(cf_F | cn_K),
    _pk_t(cf_T | cn_A), _pk_t(cf_X | cn_A), _pk_t(cf_M | cn_A), _pk_t(cf_F | cn_A)
};

typedef PokerPool<_pk_t, count_poker> dzPokerPool, _dz_pool_t, dzpool_t;

template<> void dzPokerPool::_InitializePoker() {
    for (_index_t i = 0; i < count_poker; ++i)
        _pool[i] = _gc_dz_poker_pool[i];
}

_bnb_space_out

#endif
//                                                         2014-11 by Frank
//-----------------------------------------------------------------------------