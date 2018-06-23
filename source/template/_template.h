#ifndef ____bnb_template_h_
#define ____bnb_template_h_

_bnb_space_in


template<typename _Ty>
struct unary_class {
    typedef _Ty     value_type;
};

template<typename _Ty1, typename _Ty2>
struct binary_class {
    typedef _Ty1    key_type;
    typedef _Ty2    value_type;
};

template<typename _Ty>
struct container_class
{
    typedef _Ty             value_type;
    typedef unsigned int    index_type;
    typedef unsigned int    size_type;
    typedef unsigned int    pos_type;

    const static pos_type  __invalid = 1<<((sizeof(pos_type)<<3)-1);

    enum {
        __def_size
        = sizeof(value_type) <= 1 ? 0x40
        : sizeof(value_type) <= 2 ? 0x20
        : sizeof(value_type) <= 4 ? 0x10
        : sizeof(value_type) <= 8 ? 0x08
        : 0x04,

        __max_size
        = sizeof(value_type) <= 1 ? (1<<((sizeof(size_type)<<3) - 2))
        : sizeof(value_type) <= 2 ? (1<<((sizeof(size_type)<<3) - 3))
        : sizeof(value_type) <= 4 ? (1<<((sizeof(size_type)<<3) - 4))
        : sizeof(value_type) <= 8 ? (1<<((sizeof(size_type)<<3) - 5))
        : (1<<(sizeof(size_type)<<2))
    };
};


class uncopyable_class
{
private:
    uncopyable_class(const uncopyable_class&);
    uncopyable_class& operator = (const uncopyable_class&);
};

struct ignore_operator
{
    typedef ignore_operator ignore_type;

    template<typename _Ty>
    const ignore_type& operator + (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator - (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator * (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator / (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator % (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator & (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator ~ () const { return *this; }

    template<typename _Ty>
    const ignore_type& operator | (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator ^ (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator << (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator >> (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator () (const _Ty&) const { return *this; }

    template<typename _Ty>
    const ignore_type& operator [] (const _Ty&) const { return *this; }

    template<typename _Ty>
    ignore_type& operator = (const _Ty&) { return *this; }

};  // struct ignore_operator


template<typename _Ty>
class singleton
{
protected:

    singleton() { }

public:

    virtual        ~singleton() = 0 { }

    static _Ty&     GetInstance() { static _Ty _obj; return _obj; }

};  // class Singleton

_bnb_space_out


#define _friend_singleton(name)     friend bnb::singleton<name>


#endif