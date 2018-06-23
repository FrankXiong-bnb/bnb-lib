#ifndef ____bnb_List_H_
#define ____bnb_List_H_

_bnb_space_in

template<typedef _Ty>
class SingleList
{
    typedef _Ty value_t;
    typedef struct Node {
        value_t _data;
        Node* _pNext;
    } node_t;

    _size_t Size() const;
    void Clear();

    bool PushBack(const value_t& val);
    bool PushFront(const value_t& val);
    bool PopBack();
    bool PopFront();

    template<typename _CompareT>
    bool Insert(const value_t& val, _CompareT pFun);
    bool Insert(const value_t* _Where, const value_t& val);

    template<typename _CompareT>
    value_t* Find(_CompareT pFun) const;
    value_t* Find(const value_t& val) const;

    template<typename _CompareT>
    bool Erase(_CompareT pFun) const;
    bool Erase(const value_t& val);

    const value_t* Next() const;

    node_t* _pHead;
    node_t* _pLast;
};

#include <vector>


_bnb_space_out

#endif