#ifndef ____bnb_Poker_SDB_H_
#define ____bnb_Poker_SDB_H_

#include "pk_Utils.h"

#define _poker_sdb_in     namespace _ns_sdb {
#define _poker_sdb_out    }

_poker_space_in

_poker_sdb_in

#define _pkMaxCount 5       // 牌最大张数
#define _pkmcBanker 18      // 庄家最大张数

const _value_t _gc_sdb_poker_value[_nMax] = {
    0,              // none
    2 << 1,         // 2
    3 << 1,         // 3
    4 << 1,         // 4
    5 << 1,         // 5
    6 << 1,         // 6
    7 << 1,         // 7
    8 << 1,         // 8
    9 << 1,         // 9
    10 << 1,        // 10

//  J  Q  K  A       S  B
    1, 1, 1, 1 << 1, 1, 1
};

inline _value_t _sdb_pk_value(const _pk_t& k)
{
    return _gc_sdb_poker_value[_pkNumber(k)];
}

typedef enum _sdb_poker_type
{
    spt_spillout,   // 爆点
    spt_d05,        // 半点
    spt_d10,        // 一点
    spt_d15,        // 一点半
    spt_d20,        // 两点
    spt_d25,        // 两点半
    spt_d30,        // 三点
    spt_d35,        // 三点半
    spt_d40,        // 四点
    spt_d45,        // 四点半
    spt_d50,        // 五点
    spt_d55,        // 五点半
    spt_d60,        // 六点
    spt_d65,        // 六点半
    spt_d70,        // 七点
    spt_d75,        // 七点半
    spt_d80,        // 八点
    spt_d85,        // 八点半
    spt_d90,        // 九点
    spt_d95,        // 九点半
    spt_ten,        // 十点
    spt_full,       // 十点半
    spt_fivesmall,  // 五小
    spt_fivefull,   // 天王
    spt_fiveflower, // 人小五

    spt_max
} spt_e;

template<bool> spt_e _CheckType(const _pk_t*, _size_t);

template<>
spt_e _CheckType<false>(const _pk_t* pkarr, _size_t n)
{
    if (_pkMaxCount < n) return spt_spillout;   // 张数不符合要求直接爆点

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (spt_full < (_vtsdb += _sdb_pk_value(pkarr[i])))
            return spt_spillout;    // 如果值过大直接爆点

    if (_pkMaxCount == n)   // 如果张数最大
    {
        if (_vtsdb < spt_full)   // 没有满点
        {
            for (_index_t i = 0; i < _pkMaxCount; ++i)
                if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                    return spt_fivesmall;   // 有一张不是花牌就是五小

            return spt_fiveflower;  // 否则就是人小五
        }

        return spt_fivefull;    // 否则是天王
    }

    return static_cast<spt_e>(_vtsdb);  // 否则是平牌
}

template<>
spt_e _CheckType<true>(const _pk_t* pkarr, _size_t n)
{
    // 先统计王的数量
    _size_t nCount = _ns_utils::_Count(pkarr, n, [](const _pk_t& k){ return (_pkFlower(k) == _fK); });

    if (0 == nCount)
        return _CheckType<false>(pkarr, n); // 如果没有王，按普通方式检查牌型。

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (_pkFlower(pkarr[i]) != _fK)     // 统计非王牌的点数
            if (spt_full - 1 < (_vtsdb += _sdb_pk_value(pkarr[i])))
                return spt_spillout;        // 如果值过大直接爆点

    if (1 == nCount)    // 如果只有一个王
    {
        if (_vtsdb == spt_ten || 1 == (_vtsdb % 2))
            _vtsdb = spt_full;
        else
            _vtsdb = spt_ten;

        if (_pkMaxCount == n)           // 如果张数最大
        {
            if (_vtsdb < spt_full)   // 没有满点
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivesmall;   // 有一张不是花牌就是五小

                return spt_fiveflower;          // 否则就是人小五
            }
            else
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivefull;    // 有一张不是花牌就是天王

                return spt_fiveflower;          // 否则就是人小五
            }
        }

        return static_cast<spt_e>(_vtsdb);      // 否则是平牌
    } 
    else
    {
        if (_vtsdb < spt_ten)
        {
            if (_pkMaxCount == n)   // 如果张数最大
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivefull;    // 有一张不是花牌就是天王

                return spt_fiveflower;          // 否则就是人小五
            }

            return spt_full;        // 否则就是十点半
        }

        return spt_spillout;
    }
}

template<bool> spt_e _CheckBankerType(const _pk_t*, _size_t);

template<>
spt_e _CheckBankerType<false>(const _pk_t* pkarr, _size_t n)
{
    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (spt_full < (_vtsdb += _sdb_pk_value(pkarr[i])))
            return spt_spillout;    // 如果值过大直接爆点

    return static_cast<spt_e>(_vtsdb);  // 否则是平牌
}

template<>
spt_e _CheckBankerType<true>(const _pk_t* pkarr, _size_t n)
{
    // 先统计王的数量
    _size_t nCount = _ns_utils::_Count(pkarr, n, [](const _pk_t& k){ return (_pkFlower(k) == _fK); });

    if (0 == nCount)
        return _CheckBankerType<false>(pkarr, n); // 如果没有王，按普通方式检查牌型。

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (_pkFlower(pkarr[i]) != _fK)     // 统计非王牌的点数
            if (spt_ten < (_vtsdb += _sdb_pk_value(pkarr[i])))
                return spt_spillout;        // 如果值过大直接爆点

    if (1 == nCount)    // 如果只有一个王
    {
        if (_vtsdb == spt_ten || 1 == (_vtsdb % 2))
            return spt_full;  // 十点半
        else
            return spt_ten;   // 十点
    }
    else
    {
        if (_vtsdb < spt_ten)
            return spt_full;        // 十点半
        else
            return spt_spillout;    // 爆点
    }
}

spt_e CheckType(const _pk_t* pkarr, _size_t n, bool bAny)
{
    if (bAny)
        return _CheckType<true>(pkarr, n);
    else
        return _CheckType<false>(pkarr, n);
}

spt_e CheckBankerType(const _pk_t* pkarr, _size_t n, bool bAny)
{
    if (bAny)
        return _CheckBankerType<true>(pkarr, n);
    else
        return _CheckBankerType<false>(pkarr, n);
}

// 扑克池类型
typedef _ns_utils::_pkset_base<_pkmcBanker> _pkbanker_t;
typedef _ns_utils::_pkset_base<_pkMaxCount> _sdbpkset_t;
typedef _ns_utils::_pk_pool_t<> _sdbpool_t;

_poker_sdb_out

_poker_space_out

#endif