#ifndef ____bnb_Path_H_
#define ____bnb_Path_H_

#include "class/_point.h"

namespace bnb
{
    class Path
    {

        void Clear()
        {
            if (_def_size < m_Capacity)
            {
                delete[] m_PointList._ptr;
                m_PointList._ptr = nullptr;
            }

            m_Size = 0;
            m_Capacity = _def_size;
        }

        ~Path()
        {
            if (_def_size < m_Capacity)
            {
                delete[] m_PointList._ptr;
            }
        }

    private:

        static const unsigned int _def_size = 2;

        union
        {
            Point  _arr[_def_size];
            Point* _ptr;
        } m_PointList;

        unsigned int m_Size;
        unsigned int m_Capacity;

    };
}

#endif  // ____bnb_Path_H_
