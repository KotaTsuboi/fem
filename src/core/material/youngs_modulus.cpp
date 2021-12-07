#include "youngs_modulus.hpp"
#include <cassert>

YoungsModulus::YoungsModulus(double e) : e(e) {
    assert(e > 0 && "Young's modulus must be greater than zero");
}

double YoungsModulus::Value() const {
    return e;
}
