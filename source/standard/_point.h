#ifndef ____bnb_Point_H_
#define ____bnb_Point_H_

namespace bnb
{
    class Point
    {
    public:

        Point(double x = 0, double y = 0)
        {
            m_PosX = x;
            m_PosY = y;
        }

        void SetPosX(double x) { m_PosX = x; }
        void SetPosY(double y) { m_PosY = y; }
        double GetPosX() const { return m_PosX; }
        double GetPosY() const { return m_PosY; }

        void MoveX(double x) { m_PosX += x; }
        void MoveX(double y) { m_PosY += y; }

    private:

        double m_PosX{ 0 };
        double m_PosY{ 0 };

    };

}

#endif
