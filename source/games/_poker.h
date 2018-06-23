//=============================================================================
// _poker.h
//
// Exception :
//      定义扑克表示方法以及基本算法
//
//=============================================================================
#ifndef ____bnb_poker_H_
#define ____bnb_poker_H_

#include "../standard/_definition.h"
#include "../standard/_tydef.h"

_bnb_space_in

// 扑克点数枚举
//-----------------------------------------------------------------------------

typedef enum _card_number {
    cn_unknow,  // 未知

    // 2     3     4     5     6     7     8     9    10     J     Q     K     A
    cn_2, cn_3, cn_4, cn_5, cn_6, cn_7, cn_8, cn_9, cn_T, cn_J, cn_Q, cn_K, cn_A,

    cn_S,       // 小王
    cn_B,       // 大王

    cn_max
} _pk_number_t;

// 扑克花色枚举
//-----------------------------------------------------------------------------

typedef enum _card_flower {
    cf_F        = 0x00,         // 方
    cf_M        = 0x10,         // 梅
    cf_X        = 0x20,         // 心
    cf_T        = 0x30,         // 桃
    cf_K        = 0x40,         // 王
    cf_unknow   = 0x50,         // 未知

    cf_max
} _pk_flower_t;

#define cn_mask         0x0f    // 点数检测码
#define cf_mask         0xf0    // 花色检测码
#define card_mask       0xff    // 扑克检测码

#define _invalid_card   (_bnb cn_unknow | _bnb cf_unknow)   // 无效牌

// 牌类型定义和基本操作
//-----------------------------------------------------------------------------

typedef unsigned char  card_t;  // 牌类型

inline _pk_number_t _check_pk_number(const card_t& c) {     // 检测点数
    return static_cast<_pk_number_t>(cn_mask & c);
}
inline _pk_flower_t _check_pk_flower(const card_t& c) {     // 检测花色
    return static_cast<_pk_flower_t>(cf_mask & c);
}
inline unsigned int _get_number_value(const card_t& c) {    // 获取点数值
    return (_check_pk_number(c));
}
inline unsigned int _get_flower_value(const card_t& c) {    // 获取花色值
    return (_check_pk_flower(c) >> 4);
}

// 判定两张牌是否相同
inline bool _is_identical_card(const card_t& c1, const card_t& c2) {
    return (c1 == c2);
}

// 判定点数是否相同
inline bool _is_identical_number(const card_t& c1, const card_t& c2) {
    return (_check_pk_number(c1) == _check_pk_number(c2));
}

// 判定花色是否相同
inline bool _is_identical_flower(const card_t& c1, const card_t& c2) {
    return (_check_pk_flower(c1) == _check_pk_flower(c2));
}

// 交换两张牌
inline void Swap(card_t& left, card_t& right) {
    if (left != right) left ^= right ^= left ^= right;
}

template<typename _LessT>   // 对牌数组排序
inline void Sort(card_t* poker, _size_t n, _LessT pFun)
{
    for (_index_t i = 1; i < n; ++i)
    {
        card_t* next = poker + i, key(*next);

        if (pFun(key, *poker))
        {
            for (card_t* last = next; next != poker; next = last)
                *next = *--last;

            *poker = key;
        } 
        else
        {
            for (card_t* last = next; pFun(key, *--last); next = last)
                *next = *last;

            *next = key;
        }
    }
}

//=============================================================================
// 扑克基类
//=============================================================================
template<typename _PkT> struct _poker_base
{
    typedef unsigned int    _value_t;
    typedef unsigned char   _number_t;
    typedef unsigned char   _flower_t;

    explicit _poker_base(const card_t& c = _invalid_card) : _card(c) { }

    void SetCard(const card_t& c) { _card = c; }
    const card_t& GetCard() const { return _card; }

    bool IsValid() const { return (cn_unknow != GetNumber() && cf_unknow != GetFlower()); }
    bool IsIdentical(const _poker_base& other) const { return (_card == other._card); }

    _pk_flower_t GetFlower() const { return (_check_pk_flower(_card)); }
    _pk_number_t GetNumber() const { return (_check_pk_number(_card)); }

    _value_t GetCardValue() const { return _get_number_value(_card); }
    _value_t GetFlowerValue() const { return _get_flower_value(_card); }

    _result_t Compare(const _PkT& right) const {
        if (this->GetCardValue() < right.GetCardValue()) return (-1);
        if (right.GetCardValue() < this->GetCardValue()) return (1);
        return 0;
    }

    card_t  _card;

};  // struct _poker_base

template<typename _PkT>
bool operator <  (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return (left.Compare(right) < 0);
}
template<typename _PkT>
bool operator >  (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return right < left;
}
template<typename _PkT>
bool operator <= (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return !(right < left);
}
template<typename _PkT>
bool operator >= (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return !(left < right);
}
template<typename _PkT>
bool operator == (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return left.GetCardValue() == right.GetCardValue();
}
template<typename _PkT>
bool operator != (const _poker_base<_PkT>& left, const _poker_base<_PkT>& right) {
    return !(left == right);
}

template<typename _PkT>
void Swap(_poker_base<_PkT>& left, _poker_base<_PkT>& right) {
    if (!left.IsIdentical(right)) left._card ^= right._card ^= left._card ^= right._card;
}

//=============================================================================
// 扑克特性操作
//=============================================================================
template<typename _PkT> struct _Trait_Poker
{
    typedef typename _PkT::_value_t        _value_t;
    typedef typename _PkT::_flower_t       _flower_t;
    typedef typename _PkT::_number_t       _number_t;

    // 按点数统计扑克
    static void Count(_size_t (&arr)[cn_max], const _PkT* poker, _size_t n)
    {
        for (_index_t i = 0; i < n; ++arr[poker[i++].GetNumber()]);
    }

    // 将扑克数组转化到牌数组
    static _size_t Convert(card_t* pDst, _size_t n, const _PkT* pSrc, _size_t _size)
    {
        _size_t count = (_size < n) ? _size : n;

        for (_index_t i = 0; i < count; ++i)
            pDst[i] = pSrc[i].GetCard();

        return count;
    }

    // 将牌数组转换到扑克数组
    static _size_t Convert(_PkT* pDst, _size_t n, const card_t* pSrc, _size_t _size)
    {
        _size_t count = (_size < n) ? _size : n;

        for (_index_t i = 0; i < count; ++i)
            pDst[i]._card = pSrc[i];

        return count;
    }

    // 查找满足指定条件的扑克位置
    template<typename _FindT>
    static _index_t Find(const _PkT* poker, _size_t n, _FindT pFun)
    {
        for (_index_t i = 0; i < n; ++i)
            if (pFun(poker[i]))
                return i;

        return _invalid_index;
    }

    // 查找指定扑克位置
    static _index_t Find(const _PkT* poker, _size_t n, const _PkT& pk)
    {
        return Find(poker, n, [&pk](const _PkT& _pk){ return _pk.IsIdentical(pk); });
    }

    // 拷贝扑克数组
    static _size_t Copy(_PkT* pDst, _size_t _size, const _PkT* pSrc, _size_t n)
    {
        _size = _size < n ? _size : n;

        for (_index_t i = 0; i < _size; ++i)
            pDst[i] = pSrc[i];

        return _size;
    }

    // 拷贝牌数组
    static _size_t Copy(_PkT* pDst, _size_t _size, const card_t* pSrc, _size_t n)
    {
        _size = _size < n ? _size : n;

        for (_index_t i = 0; i < _size; ++i)
            pDst[i]._card = pSrc[i];

        return _size;
    }

    // 排序扑克数组
    template<typename _LessT>
    static void Sort(_PkT* poker, _size_t n, _LessT pFun)
    {
        for (_index_t i = 1; i < n; ++i)
        {
            _PkT* next = poker + i, key(*next);

            if (pFun(key, *poker))
            {
                for (_PkT* last = next; next != poker; next = last)
                    *next = *--last;

                *poker = key;
            } 
            else
            {
                for (_PkT* last = next; pFun(key, *--last); next = last)
                    *next = *last;

                *next = key;
            }
        }
    }

    static void Sort(_PkT* poker, _size_t n)
    {
        Sort(poker, n, [](const _PkT& left, const _PkT& rigth){ return (left < rigth); });
    }

    // 查找扑克极值
    template<typename _LessT>
    static _index_t Limit(const _PkT* poker, _size_t n, _LessT pFun)
    {
        if (n > 0)
        {
            _index_t pos = 0;

            for (_index_t i = 1; i < n; ++i)
                if (pFun(poker[pos], poker[i]))
                    pos = i;

            return pos;
        }

        return _invalid_index;
    }

    template<typename _LessT>
    static _index_t Limit(const _PkT* poker, _size_t n, _LessT pFun, const _value_t& v)
    {
        return LimitIf(poker, n, pFun, [&v](const _PkT& p){ return p.GetCardValue() == v; });
    }

    static _index_t Limit(const _PkT* poker, _size_t n, const _value_t& v)
    {
        return Limit(poker, n, [](const _PkT& left, const _PkT& rigth){ return (left < rigth); }, v);
    }

    static _index_t Limit(const _PkT* poker, _size_t n)
    {
        return Limit(poker, n, [](const _PkT& left, const _PkT& rigth){ return (left < rigth); });
    }

    // 查找满足条件的扑克极值
    template<typename _LessT, typename _FindT>
    static _index_t LimitIf(const _PkT* poker, _size_t n, _LessT pLess, _FindT pFind)
    {
        _index_t pos = Find(poker, n, pFind);

        if (_invalid_index != pos)
            for (_index_t i = pos+1; i < n; ++i)
                if (pFind(poker[i]))
                    if (pLess(poker[pos], poker[i]))
                        pos = i;

        return pos;    
    }

    template<typename _FindT>
    static _index_t LimitIf(const _PkT* poker, _size_t n, _FindT pFind)
    {
        return LimitIf(poker, n, [](const _PkT& left, const _PkT& rigth){ return (left < rigth); }, pFind);
    }

    static const _index_t   _invalid_index  = (_index_t)(-1);

};  // struct _Trait_Poker

//=============================================================================
// 扑克组基类
//=============================================================================
template<typename _PokerT, _size_t _Count> class PokerSetBase
{    
    static_assert(_Count > 0, "The template parameter _Count must be greater than 0.");

protected:

    typedef _PokerT                         _PkT_;
    typedef PokerSetBase<_PkT_, _Count>     _BaseT_;
    typedef _Trait_Poker<_PkT_>             _TraitT_;

    typedef typename _PkT_::_value_t        _value_t;
    typedef typename _PkT_::_flower_t       _flower_t;
    typedef typename _PkT_::_number_t       _number_t;

public:

    _BaseT_() { Clear(); }
    _BaseT_(const _PkT_* pSet, _size_t n) { Assign(pSet, n); }
    _BaseT_(const card_t* pSet, _size_t n) { Assign(pSet, n); }

    _PkT_& operator [] (_index_t index) { return _poker[index]; }

    const _PkT_& operator [] (_index_t index) const { return _poker[index]; }

    _size_t GetSize() const { return _size; }

    const _PkT_* GetPoker() const { return _poker; }

    template<typename _FunT>
    _index_t GetMaxPoker(_FunT pFun) const                  // 获取最大的扑克
    {
        return _TraitT_::Limit(_poker, _size, pFun);
    } 

    _index_t GetMaxPoker() const
    {
        return GetMaxPoker([](const _PkT& left, const _PkT& rigth){ return (left < rigth); });
    }

    _index_t GetMaxPoker(const _value_t& pkvalue) const     // 获取指定牌值的最大扑克(可能是指定牌值中花色最大的)
    {
        return _TraitT_::Limit(_poker, _size, pkvalue, [](const _PkT& left, const _PkT& rigth){ return (left < rigth); });
    }

    template<typename _FunT>
    _index_t GetMinPoker(_FunT pFun) const                  // 获取最小的扑克
    {
        return _TraitT_::Limit(_poker, _size, [](const _PkT& left, const _PkT& rigth){ return pFun(rigth < left); });
    }

    _index_t GetMinPoker() const
    {
        return GetMinPoker([](const _PkT& left, const _PkT& rigth){ return (left < rigth); });
    }

    _index_t GetMinPoker(const _value_t& pkvalue) const     // 获取指定牌值的最小扑克(可能是指定牌值中花色最小的)
    {
        return _TraitT_::Limit(_poker, _size, pkvalue, [](const _PkT& left, const _PkT& rigth){ return (rigth < left); });
    }

    void Clear()                                            // 清空
    {
        for (int i = 0; i < _Count; ++i)
            _poker[i]._card = _invalid_card;

        _size = 0;
    }

    _index_t Find(const _PkT_& pk) const                    // 查找指定扑克
    {
        return _TraitT_::Find(_poker, _size, pk);
    }

    _index_t Find(const _value_t& pkvalue) const            // 查找指定牌值的扑克
    {
        return _TraitT_::Find(_poker, _size, [&pkvalue](const _PkT_& pk){ return pk.GetCardValue() == pkvalue; });
    }

    _size_t ConvertTo(card_t* arr, _size_t n) const         // 导出扑克数组
    {
        return _TraitT_::Convert(arr, n, _poker, _size);
    }

    bool Swap(_index_t p1, _index_t p2)                     // 交换两个位置的扑克
    {
        if (p1 < _size && p2 < _size)
        {
            if (p1 != p2)
                _bnb Swap(_poker[p1], _poker[p2]);

            return true;
        }

        return false;
    }

    template<typename _LessT>
    void Sort(_LessT pFun)                                  // 排序扑克数组
    {
        _TraitT_::Sort(_poker, _size, pFun);
    }

    void Sort()
    {
        Sort([](const _PkT_& left, const _PkT_& right){ return left < right; });
    }

    bool IsInclude(const card_t* arr, _size_t n) const
    {
        for (_index_t i = 0; i < n; ++i)
            if (invalid_index == _TraitT_::Find(_poker, _size, [&arr, &i](const _PkT_& pk){ return pk.GetCard() == arr[i]; }))
                return false;

        return true;
    }

    template<_size_t n>
    bool IsInclude(const card_t (&_pSet)[n]) const { return IsInclude(_pSet, n); }

    bool IsInclude(const _PkT_* pSet, _size_t n) const      // 判断是否包含扑克子集
    {
        for (int i = 0; i < n; ++i)
            if (invalid_index == Find(pSet[i]))
                return false;

        return true;
    }

    template<_size_t n>
    bool IsInclude(const _PkT_ (&_pSet)[n]) const { return IsInclude(_pSet, n); }

    _size_t Assign(const card_t* arr, _size_t n)            // 将一组牌数据赋给类对象
    {
        _size = _Count < n ? _Count : n;

        for (_index_t i = 0; i < _size; ++i)
            _poker[i]._card = arr[i];

        return _size;
    }

    template<_size_t n>
    _size_t Assign(const card_t (&arr)[n]) { return Assign(arr, n); }

    _size_t Assign(const _PkT_* pSet, _size_t n)
    {
        _size = _Count < n ? _Count : n;

        for (_index_t i = 0; i < _size; ++i)
            _poker[i] = pSet[i];

        return _size;
    }

    template<_size_t n>
    _size_t Assign(const _PkT_ (&_pSet)[n]) { return Assign(_pSet, n); }

    bool Remove(const _PkT_& pk)                            // 删除一张指定扑克
    {
        for (_index_t i = 0; i < _size; ++i)
        {
            if (_poker[i].IsIdentical(pk))
            {
                for (_index_t j = i + 1; j < _size; ++j)
                    _poker[j - 1] = _poker[j];

                --_size;
                return true;
            }
        }

        return false;
    }

    _size_t Remove(_BaseT_& pk)            // 删除一组扑克
    {
        _size_t count = 0;

        for (_index_t next = 0; next < _size; ++next)
        {
            if (pk.Remove(_poker[next]))
            {
                for (_index_t last = next++; next < _size; ++next)
                    if (pk.Remove(_poker[next]))
                        ++count;
                    else
                        _poker[last++] = _poker[next];

                _size -= ++count;
                break;
            }
        }

        return count;
    }

    _size_t Remove(const _PkT_* pSet, _size_t n)            // 删除一组扑克
    {
        return Remove(_BaseT_(pSet, n));
    }

    _size_t Remove(const card_t* pSet, _size_t n)           // 删除一组扑克
    {
        return Remove(_BaseT_(pSet, n));
    }

    bool Append(const card_t& pk)                           // 追加一张扑克
    {
        if (_size < _Count)
        {
            _poker[_size++].SetCard(pk);
            return true;
        }

        return false;
    }

    _size_t Append(const card_t* pSet, _size_t n)           // 追加一组扑克
    {
        _size_t count = ((_Count - _size) < n) ? (_Count - _size) : n;

        for (_index_t i = 0; i < count; ++i, ++_size)
            _poker[_size].SetCard(pSet[i]);

        return count;
    }

    template<_size_t n>
    _size_t Append(const card_t (&arr)[n])
    {
        return Append(arr, n);
    }

    bool Append(const _PkT_& pk)
    {
        return Append(pk.GetCard());
    }

    _size_t Append(const _PkT_* pSet, _size_t n)
    {
        _size_t count = ((_Count - _size) < n) ? (_Count - _size) : n;

        for (_index_t i = 0; i < count; ++i, ++_size)
            _poker[_size] = pSet[i];

        return count;
    }

    template<_size_t n>
    _size_t Append(const _PkT_ (&arr)[n])
    {
        return Append(arr, n);
    }

protected:

    _size_t _size;
    _PkT_   _poker[_Count];

public:

    static const _index_t   invalid_index  = _TraitT_::_invalid_index;

};  // class PokerSetBase

//=============================================================================
// 扑克池
//=============================================================================
template<typename _PokerT, _size_t _Size>
class PokerPool
{
    static_assert(_Size > 0, "The template parameter _Size must be greater than 0.");

private:

    typedef _PokerT                 _PkT_;
    typedef PokerPool<_PkT_, _Size> _MyT_;

    void _InitializePoker() // 初始化扑克池(需要改写)
    {    
        for (_index_t i = 0; i < _Size; ++i)
            _pool[i]._card = _invalid_card;
    }

public:

    PokerPool() : _index(0) { _InitializePoker(); }

    PokerPool(const _PkT_ (&pset)[_Size]) : _index(0)
    {
        for (_index_t i = 0; i < _Size; ++i) _pool[i] = pset[i];
    }

    PokerPool(const card_t (&pset)[_Size]) : _index(0)
    {
        for (_index_t i = 0; i < _Size; ++i) _pool[i].SetCard(pset[i]);
    }

    _PkT_& operator [] (_index_t index) { return _pool[_index % _Size]; }

    const _PkT_& operator [] (_index_t index) const { return _pool[index % _Size]; }

    _size_t GetRemain() const { _index %= _Size; return (_Size - _index); } // 获取剩余牌数量

    const _index_t& GetIndex()  const { return _index; }

    void SetIndex(const _index_t& index) { _index = index; }

    void Assign(const _PkT_ (&arr)[_Size])
    {
        _index = 0;
        for (_index_t i = 0; i < _Size; ++i) _pool[i] = arr[i];
    }

    void Assign(const card_t (&arr)[_Size])
    {
        _index = 0;
        for (_index_t i = 0; i < _Size; ++i) _pool[i].SetCard(arr[i]);
    }

    const _PkT_& Extract() const { return _pool[(_index++) % _Size]; }  // 提取当前扑克

    card_t* Extract(card_t* arr, _size_t n) const // 提取一组扑克
    {
        for (_index_t i = 0; i < n; ++i, ++_index)
            arr[i] = _pool[_index % _Size].GetCard();

        return arr;
    }

    template<_size_t n>
    card_t* Extract(card_t (&arr)[n]) const { return Extract(arr, n); }

    _PkT_* Extract(_PkT_* arr, _size_t n) const // 提取一组扑克
    {
        for (_index_t i = 0; i < n; ++i, ++_index)
            arr[i] = _pool[_index % _Size];

        return arr;
    }

    template<_size_t n>
    _PkT_* Extract(_PkT_ (&arr)[n]) const { return Extract(arr, n); }

    template<typename _RandT>
    void Shuffle(_RandT _pf)    // 打乱扑克池
    {
        for (_index_t i = _Size - 1; i > 0; --i)
            Swap(_pool[i], _pool[_pf(0, i)]);
    }

    void Reset()    // 重置
    {
        _index = 0;
        _InitializePoker();
    }

private:

    _PkT_               _pool[_Size];           // 扑克池
    mutable _index_t    _index;                 // 当前索引

};  // class PokerPool

_bnb_space_out

#endif
//                                                         2014-7 by Frank
//-----------------------------------------------------------------------------