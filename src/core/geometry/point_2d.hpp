#pragma once

#include "point.hpp"

class Point2D : public Point {
  public:
    Point2D();

    Point2D(double x, double y);

    double X() const;

    double Y() const;

    double Z() const;

    bool operator=(Point2D &aPoint);

  private:
    double x;
    double y;
    unsigned int node_index;
    static int num_node;
};

