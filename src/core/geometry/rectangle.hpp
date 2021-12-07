#pragma once

#include "point.hpp"
#include "point_2d.hpp"

class Rectangle {
  public:
    Rectangle(Point &p1, Point &p2);
    double MinX() const;
    double MinY() const;
    double MaxX() const;
    double MaxY() const;
    double Width() const;
    double Height() const;
    ~Rectangle() = default;

  private:
    Point2D _p1;
    Point2D _p2;
    double w;
    double h;
};

