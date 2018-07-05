#ifndef ____bnb_Rectangle_H_
#define ____bnb_Rectangle_H_

#include "class/_point.h"

namespace bnb
{
    class Rectangle
    {
    public:

        Rectangle(Point p, double width, double height)
            : _pos(p), _w(width), _h(height)
        { }
        Rectangle(double top, double bottom, double left, double right)
            : _pos(left, top), _w(right - left), _h(bottom - top)
        { }

        const Point& GetPos() const { return _pos; }
        double GetWidth() const { return _w; }
        double GetHeight() const { return _h; }

        double Left() const { return _pos.GetPosX(); }
        double Right() const { return (Left() + _w); }
        double Top() const { return _pos.GetPosY(); }
        double Bottom() const { return (Top() + _h); }

        bool IsValid() const { return (0 < _w && 0 < _h); }
        bool IsEmpty() const { return (_w == 0.0 && _h == 0.0); }

        bool Contains(const Rectangle &r) const
        {



            return false;
        }
        bool Contains(const Point &p) const
        {


            return false;
        }

        void SetTop(double x) { double diff = x - _pos.GetPosY(); _pos.MoveY(diff); _h -= diff; }
        void SetBottom(double x) { _h = x - _pos.GetPosY(); }
        void SetLeft(double x) { double diff = x - _pos.GetPosX(); _pos.MoveX(diff); _w -= diff; }
        void SetRight(double x) { _w = x - _pos.GetPosX(); }

        void MoveTop(double y) { _pos.SetPosY(y); }
        void MoveBottom(double y) { _pos.SetPosY(y - _h); }
        void MoveLeft(double x) { _pos.SetPosX(x); }
        void MoveRight(double x) { _pos.SetPosX(x - _w); }

        void MoveTo(double x, double y) { _pos.SetXY(x, y); }
        void Translate(double x, double y) { _pos.MoveXY(x, y); }

    private:

        Point _pos;
        double _w, _h;

    };

    inline Rectangle operator | (const Rectangle& a, const Rectangle& b)
    {

    }

    inline Rectangle operator & (const Rectangle& a, const Rectangle& b)
    {

    }

}

#endif
