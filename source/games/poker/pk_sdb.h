#ifndef ____bnb_Poker_SDB_H_
#define ____bnb_Poker_SDB_H_

#include "pk_Utils.h"

#define _poker_sdb_in     namespace _ns_sdb {
#define _poker_sdb_out    }

_poker_space_in

_poker_sdb_in

#define _pkMaxCount 5       // ���������
#define _pkmcBanker 18      // ׯ���������

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
    spt_spillout,   // ����
    spt_d05,        // ���
    spt_d10,        // һ��
    spt_d15,        // һ���
    spt_d20,        // ����
    spt_d25,        // �����
    spt_d30,        // ����
    spt_d35,        // �����
    spt_d40,        // �ĵ�
    spt_d45,        // �ĵ��
    spt_d50,        // ���
    spt_d55,        // ����
    spt_d60,        // ����
    spt_d65,        // �����
    spt_d70,        // �ߵ�
    spt_d75,        // �ߵ��
    spt_d80,        // �˵�
    spt_d85,        // �˵��
    spt_d90,        // �ŵ�
    spt_d95,        // �ŵ��
    spt_ten,        // ʮ��
    spt_full,       // ʮ���
    spt_fivesmall,  // ��С
    spt_fivefull,   // ����
    spt_fiveflower, // ��С��

    spt_max
} spt_e;

template<bool> spt_e _CheckType(const _pk_t*, _size_t);

template<>
spt_e _CheckType<false>(const _pk_t* pkarr, _size_t n)
{
    if (_pkMaxCount < n) return spt_spillout;   // ����������Ҫ��ֱ�ӱ���

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (spt_full < (_vtsdb += _sdb_pk_value(pkarr[i])))
            return spt_spillout;    // ���ֵ����ֱ�ӱ���

    if (_pkMaxCount == n)   // ����������
    {
        if (_vtsdb < spt_full)   // û������
        {
            for (_index_t i = 0; i < _pkMaxCount; ++i)
                if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                    return spt_fivesmall;   // ��һ�Ų��ǻ��ƾ�����С

            return spt_fiveflower;  // ���������С��
        }

        return spt_fivefull;    // ����������
    }

    return static_cast<spt_e>(_vtsdb);  // ������ƽ��
}

template<>
spt_e _CheckType<true>(const _pk_t* pkarr, _size_t n)
{
    // ��ͳ����������
    _size_t nCount = _ns_utils::_Count(pkarr, n, [](const _pk_t& k){ return (_pkFlower(k) == _fK); });

    if (0 == nCount)
        return _CheckType<false>(pkarr, n); // ���û����������ͨ��ʽ������͡�

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (_pkFlower(pkarr[i]) != _fK)     // ͳ�Ʒ����Ƶĵ���
            if (spt_full - 1 < (_vtsdb += _sdb_pk_value(pkarr[i])))
                return spt_spillout;        // ���ֵ����ֱ�ӱ���

    if (1 == nCount)    // ���ֻ��һ����
    {
        if (_vtsdb == spt_ten || 1 == (_vtsdb % 2))
            _vtsdb = spt_full;
        else
            _vtsdb = spt_ten;

        if (_pkMaxCount == n)           // ����������
        {
            if (_vtsdb < spt_full)   // û������
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivesmall;   // ��һ�Ų��ǻ��ƾ�����С

                return spt_fiveflower;          // ���������С��
            }
            else
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivefull;    // ��һ�Ų��ǻ��ƾ�������

                return spt_fiveflower;          // ���������С��
            }
        }

        return static_cast<spt_e>(_vtsdb);      // ������ƽ��
    } 
    else
    {
        if (_vtsdb < spt_ten)
        {
            if (_pkMaxCount == n)   // ����������
            {
                for (_index_t i = 0; i < _pkMaxCount; ++i)
                    if (_pkNumber(pkarr[i]) < _nJ || _pkNumber(pkarr[i]) == _nA)
                        return spt_fivefull;    // ��һ�Ų��ǻ��ƾ�������

                return spt_fiveflower;          // ���������С��
            }

            return spt_full;        // �������ʮ���
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
            return spt_spillout;    // ���ֵ����ֱ�ӱ���

    return static_cast<spt_e>(_vtsdb);  // ������ƽ��
}

template<>
spt_e _CheckBankerType<true>(const _pk_t* pkarr, _size_t n)
{
    // ��ͳ����������
    _size_t nCount = _ns_utils::_Count(pkarr, n, [](const _pk_t& k){ return (_pkFlower(k) == _fK); });

    if (0 == nCount)
        return _CheckBankerType<false>(pkarr, n); // ���û����������ͨ��ʽ������͡�

    _value_t _vtsdb = 0;
    for (_index_t i = 0; i < n; ++i)
        if (_pkFlower(pkarr[i]) != _fK)     // ͳ�Ʒ����Ƶĵ���
            if (spt_ten < (_vtsdb += _sdb_pk_value(pkarr[i])))
                return spt_spillout;        // ���ֵ����ֱ�ӱ���

    if (1 == nCount)    // ���ֻ��һ����
    {
        if (_vtsdb == spt_ten || 1 == (_vtsdb % 2))
            return spt_full;  // ʮ���
        else
            return spt_ten;   // ʮ��
    }
    else
    {
        if (_vtsdb < spt_ten)
            return spt_full;        // ʮ���
        else
            return spt_spillout;    // ����
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

// �˿˳�����
typedef _ns_utils::_pkset_base<_pkmcBanker> _pkbanker_t;
typedef _ns_utils::_pkset_base<_pkMaxCount> _sdbpkset_t;
typedef _ns_utils::_pk_pool_t<> _sdbpool_t;

_poker_sdb_out

_poker_space_out

#endif