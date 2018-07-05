#ifndef ____bnb_Point_H_
#define ____bnb_Point_H_

#include "utility/_math.h"

namespace bnb
{
    class Point
    {
    public:

        Point(double x = 0, double y = 0) : _posX(x), _posY(y) { }
        Point(const Point& p) : _posX(p._posX), _posY(p._posY) { }
        Point& operator=(const Point& p)
        {
            if (this != &p)
                SetXY(p._posX, p._posY);

            return *this;
        }

        double GetPosX() const { return _posX; }
        double GetPosY() const { return _posY; }

        void SetPosX(double x) { _posX = x; }
        void SetPosY(double y) { _posY = y; }
        void SetXY(double x, double y) { SetPosX(x); SetPosY(y); }

        void MoveX(double x) { _posX += x; }
        void MoveY(double y) { _posY += y; }
        void MoveXY(double x, double y) { _posX += x; _posY += y; }

    private:

        double _posX;
        double _posY;

    };

    inline bool operator==(const Point& a, const Point& b)
    {
        return (&a == &b || (is_zero(a.GetPosX() - b.GetPosX()) && is_zero(a.GetPosY() - b.GetPosY())));
    }

}

#endif
