#include "point_2d.hpp"

Point2D::Point2D()
    : x(0),
      y(0) {
}

Point2D::Point2D(double x, double y)
    : x(x),
      y(y) {
}

double Point2D::X() const {
    return x;
}

double Point2D::Y() const {
    return y;
}

double Point2D::Z() const {
    return 0;
}

bool Point2D::operator=(Point2D &aPoint) {
    if (this->X() != aPoint.X()) {
        return false;
    }

    if (this->Y() != aPoint.Y()) {
        return false;
    }

    return true;
}

