#ifndef ____bnb_Poker_Define_H_
#define ____bnb_Poker_Define_H_

#define _poker_space_in     namespace _ns_poker {
#define _poker_space_out    }

_poker_space_in

typedef unsigned char _pk_t;
typedef unsigned int _size_t;
typedef unsigned int _index_t;
typedef unsigned int _value_t;
typedef unsigned long _param_t;

// 扑克点数枚举
//-----------------------------------------------------------------------------

typedef enum _card_number : unsigned char {
//    none    2    3    4    5    6    7    8    9   10    J    Q    K    A
    _nNone, _n2, _n3, _n4, _n5, _n6, _n7, _n8, _n9, _nT, _nJ, _nQ, _nK, _nA,

    _nS,       // 小王
    _nB,       // 大王

    _nMax
} _pk_number_t;

// 扑克花色枚举
//-----------------------------------------------------------------------------

typedef enum _card_flower : unsigned char {
    _fF = 0x00,         // 方
    _fM = 0x10,         // 梅
    _fX = 0x20,         // 心
    _fT = 0x30,         // 桃
    _fK = 0x40,         // 王
    _fNone = 0x50,      // 未知

    _fMax = 0x06
} _pk_flower_t;

#define _nMask  0x0f    // 点数检测码
#define _fMask  0xf0    // 花色检测码
#define _pMask  0xff    // 扑克检测码

// 检测点数
//-----------------------------------------------------------------------------
inline _pk_number_t _pkNumber(const _pk_t& k)
{
    return static_cast<_pk_number_t>(_nMask & k);
}

// 检测花色
//-----------------------------------------------------------------------------
inline _pk_flower_t _pkFlower(const _pk_t& k)
{
    return static_cast<_pk_flower_t>(_fMask & k);
}

// 生成点数索引
inline _index_t _npkIndex(const _pk_t& k) { return (_pkNumber(k)); }

// 生成花色索引
inline _index_t _fpkIndex(const _pk_t& k) { return (_pkFlower(k) >> 4); }

// 判定点数是否相同
//-----------------------------------------------------------------------------

inline bool _IsEqualNumber(const _pk_t& k1, const _pk_t& k2)
{
    return (_pkNumber(k1) == _pkNumber(k2));
}

// 判定花色是否相同
//-----------------------------------------------------------------------------

inline bool _IsEqualFlower(const _pk_t& k1, const _pk_t& k2)
{
    return (_pkFlower(k1) == _pkFlower(k2));
}

// 判定两个数是否和另外两个数相同
//-----------------------------------------------------------------------------

inline bool _IsEqualDigit(const _value_t& t1, const _value_t& t2, const _value_t& k1, const _value_t& k2)
{
    return (((1 << t1) | (1 << t2)) == ((1 << k1) | (1 << k2)));
}

_poker_space_out

#endif