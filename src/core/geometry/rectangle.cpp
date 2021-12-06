#include "rectangle.hpp"
#include "point.hpp"

#include <algorithm>
#include <cmath>

using std::abs;
using std::min;
using std::max;

Rectangle::Rectangle(Point &p1, Point &p2)
    : _p1(Point2D(min(p1.X(), p2.X()), min(p1.Y(), p2.Y()))),
    _p2(Point2D(max(p1.X(), p2.X()), max(p1.Y(), p2.Y()))),
    w(abs(p2.X() - p1.X())),
    h(abs(p2.Y() - p1.Y())) {
    }

double Rectangle::MinX() const {
    return _p1.X();
}

double Rectangle::MinY() const {
    return _p1.Y();
}

double Rectangle::MaxX() const {
    return _p2.X();
}

double Rectangle::MaxY() const {
    return _p2.Y();
}

double Rectangle::Width() const {
    return w;
}

double Rectangle::Height() const {
    return h;
}

