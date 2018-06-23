#ifndef ____bnb_Variant_H_
#define ____bnb_Variant_H_

namespace bnb
{

enum _var_type
{
    vt_none,
    vt_char,
    vt_short,
    vt_int,
    vt_long,
    vt_float,
    vt_double,
    vt_longlong,
    vt_longdouble,
};


struct _variant_value
{
    typedef _var_type       _vtT;

    _vtT   _vt;
    union {
        char                _VarChar;
        int                 _VarInt;
    } _var;
};

class Variant : public _variant_value
{
    typedef Variant         _MyT;
    typedef _variant_value  _vvT;

    ~Variant();
    Variant();

    operator char () const;
    _MyT& operator=(const char& );
    bool operator == (const _MyT& ) const;
    bool operator != (const _MyT& ) const;

    void Clear();

    void Attach(_MyT& varSrc) ;
    _MyT Detach() ;

    _vvT& GetVariant();
    _vvT* GetAddress();
    _vtT  SeeType() const;

    void ChangeType(_vtT vartype, const _MyT* pSrc = nullptr);
};


}

#endif