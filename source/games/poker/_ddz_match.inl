
typedef unsigned int _pkbit_t;      // 以点数数量组成的索引
#define _MaxExtractCount   8        // 一组牌的最大提取数量

// 生成点数数量索引
//-----------------------------------------------------------------------------

inline _pkbit_t _MakeNumberCountIndex(const _size_t (&arr)[_nMax])
{
    _pkbit_t ib = 0;

    for (_index_t i = 0; i < _nMax; ++i)
        ib |= (arr[i] << (i << 1));

    return ib;
}

inline _pkbit_t _MakeNumberCountIndex(const _pk_t* pk, int n)
{
    _size_t arr[_nMax] = { 0 };
    _Count(arr, pk, n);

    return _MakeNumberCountIndex(arr);
}

template<_size_t n>
inline _pkbit_t _MakeNumberCountIndex(const _pk_t(&pk)[n])
{
    return _MakeNumberCountIndex(pk, n);
}

// 字符和点数映射
//-----------------------------------------------------------------------------

class _pkstrmap_t
{
    static _pk_number_t _pk_map[0xFF]; // 映射表

    _pkstrmap_t() {
        _pk_map['2'] = _n2;
        _pk_map['3'] = _n3;
        _pk_map['4'] = _n4;
        _pk_map['5'] = _n5;
        _pk_map['6'] = _n6;
        _pk_map['7'] = _n7;
        _pk_map['8'] = _n8;
        _pk_map['9'] = _n9;
        _pk_map['T'] = _nT;
        _pk_map['J'] = _nJ;
        _pk_map['Q'] = _nQ;
        _pk_map['K'] = _nK;
        _pk_map['A'] = _nA;
        _pk_map['S'] = _nS;
        _pk_map['B'] = _nB;

        _pk_map['t'] = _nT;
        _pk_map['j'] = _nJ;
        _pk_map['q'] = _nQ;
        _pk_map['k'] = _nK;
        _pk_map['a'] = _nA;
        _pk_map['s'] = _nS;
        _pk_map['b'] = _nB;
    }

public:

    static const _pk_number_t& _GetPoker(const unsigned char& c)
    {
        static _pkstrmap_t hello;
        return _pk_map[c];
    }
};

__declspec(selectany) _pk_number_t _pkstrmap_t::_pk_map[0xFF] = { _nNone };

//_pk_number_t _pkstrmap_t::_pk_map[0xFF] = { _nNone };

// 剔除字符串中的空格
inline _size_t _EraseSpace(char* src)
{
    _size_t n = 0;

    for (_index_t i = 0; src[i]; ++i)
        if (' ' != src[i])
            src[n++] = src[i];

    src[n] = '\0';

    return n;
}

// 根据文本生成点数统计数据
//-----------------------------------------------------------------------------

inline void _CountString(_size_t(&arr)[_nMax], const unsigned char* str)
{
    while (*str)
        ++arr[_pkstrmap_t::_GetPoker(*str++)];
}

// 根据文本生成点数数量索引
//-----------------------------------------------------------------------------

inline _pkbit_t _StringToCountIndex(const unsigned char* str)
{
    _size_t arr[_nMax] = { 0 };
    _CountString(arr, str);

    return (_MakeNumberCountIndex(arr));
}

// 序列化牌型提取文本
//-----------------------------------------------------------------------------

static const unsigned char _gc_ext_split(',');

inline void _StringToExtractList(_pk_number_t(&t)[_dpkcPlayer], _size_t(&n)[_MaxExtractCount], const unsigned char* str)
{
    for (_index_t i = 0, j = 0; i < _dpkcPlayer && j < _MaxExtractCount && *str; ++str)
    {
        if (_gc_ext_split == *str)
        {
            ++j;
        }
        else
        {
            t[i++] = _pkNumber(_pkstrmap_t::_GetPoker(*str));
            ++n[j];
        }
    }
}

// 索引位结构
//-----------------------------------------------------------------------------

union _dpk_index_bit_t {
    _pkbit_t _k;

    struct {
        _pkbit_t _xN : 2;
        _pkbit_t _x2 : 2;
        _pkbit_t _x3 : 2;
        _pkbit_t _x4 : 2;
        _pkbit_t _x5 : 2;
        _pkbit_t _x6 : 2;
        _pkbit_t _x7 : 2;
        _pkbit_t _x8 : 2;
        _pkbit_t _x9 : 2;
        _pkbit_t _xT : 2;
        _pkbit_t _xJ : 2;
        _pkbit_t _xQ : 2;
        _pkbit_t _xK : 2;
        _pkbit_t _xA : 2;
        _pkbit_t _xS : 2;
        _pkbit_t _xB : 2;
    } _x;
};

inline bool operator < (const _dpk_index_bit_t& left, const _dpk_index_bit_t& right)
{
    return (left._k < right._k);
}

inline bool operator == (const _dpk_index_bit_t& left, const _dpk_index_bit_t& right)
{
    return (left._k == right._k);
}

// 拆牌数据结构
//-----------------------------------------------------------------------------

struct _dpk_split_t
{
    _dpk_split_t()
    {
        for (_index_t i = 0; i < _dpkcPlayer; _t[i++] = _nNone);
        for (_index_t i = 0; i < _MaxExtractCount; _n[i++] = 0);
    }

    _dpk_split_t(const unsigned char* strSplit)
    {
        for (_index_t i = 0; i < _dpkcPlayer; _t[i++] = _nNone);
        for (_index_t i = 0; i < _MaxExtractCount; _n[i++] = 0);

        Serialize(strSplit);
    }

    void Serialize(const unsigned char* strSplit)
    {
        _StringToExtractList(_t, _n, strSplit);
    }

    _pk_number_t _t[_dpkcPlayer];   // 以牌型点数排列的数组
    _size_t _n[_MaxExtractCount];   // 划分 _v 牌型的数量
};

// 匹配拆牌数据
//-----------------------------------------------------------------------------

class _pk_split_t
{
    typedef std::map<_dpk_index_bit_t, _dpk_split_t> _pk_extract_t;
    typedef _pk_extract_t::value_type value_type;

public:
    _pk_split_t() { }    
    _pk_split_t(const char* file) { Serialize(file); }

    bool Serialize(const char* file)
    {
        std::ifstream fin;
        fin.open(file, std::ios::in);

        if (!fin.is_open()) return false;

        char str[128] = { 0 };

        for (_dpk_index_bit_t dib;;)
        {
            if (!fin.getline(str, 128)) break;

            _EraseSpace(str);
            dib._k = _StringToCountIndex((unsigned char*)str);

            if (!fin.getline(str, 128)) break;

            _EraseSpace(str);
            _dpk_split_t dst((unsigned char*)str);

            _pkexmap.insert(value_type(dib, dst));
        }

        fin.close();

        return true;
    }

    // 匹配已有的拆牌方案
    _size_t ExtractMatch(_pklist_t& pklist, _pk_t* src, _size_t nsrc) const
    {
        _size_t count = 0;

        _dpk_index_bit_t key;
        key._k = _MakeNumberCountIndex(src, nsrc);

        auto iter = _pkexmap.find(key);
        if (iter != _pkexmap.end())
        {
            _size_t len = 0;
            const _pk_number_t* np = iter->second._t;

            for (_index_t i = 0; i < _MaxExtractCount && (len = iter->second._n[i]); ++i, np += len)
            {
                _pk_t pkarr[_dpkcPlayer] = { 0 };
                unsigned char _index_map[4] = { 0 };

                _size_t n = 0;

                for (_index_t t = 0, k = 0; t < nsrc; ++t)
                {
                    if ([&np, &len](const _pk_t& key, unsigned char (&_imap)[4])mutable->bool{
                            for (_index_t i = 0; i < len; ++i)
                            {
                                if (!_GetIndexMap(_imap, i))
                                {
                                    if (_pkNumber(key) == np[i])
                                    {
                                        _SetIndexMap(_imap, i);
                                        return true;
                                    }
                                }
                            }

                            return false;
                        }(src[t], _index_map))
                        pkarr[n++] = src[t];
                    else
                        src[k++] = src[t];
                }

                nsrc -= n;
                count += n;
                pklist.Add(_pkarr_t(pkarr, n));
            }
        }

        return count;
    }

    void Clear() { _pkexmap.clear(); }

private:

    _pk_extract_t _pkexmap;

};

#define _ddzSplitFile   "ddzSplit.ini"
const _pk_split_t _gc_dpk_split(_ddzSplitFile);
