#pragma once

#include <iostream>

using std::ostream;

enum class Axis2D {
    X = 0,
    Y = 1,
    END
};

Axis2D begin(Axis2D);
Axis2D end(Axis2D);
Axis2D operator*(Axis2D axis);
Axis2D operator++(Axis2D &axis);
ostream &operator<<(ostream &os, Axis2D axis);
