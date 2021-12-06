#include "youngs_modulus.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

YoungsModulus::YoungsModulus(double e) : e(e) {
    assert(e > 0 && "Young's modulus must be greater than zero");
}

double YoungsModulus::Value() const {
    return e;
}

YoungsModulus::~YoungsModulus() {
}

/*
const YoungsModulus YoungsModulus::Steel() {
    static const YoungsModulus steel(205000);
    return steel;
}

const YoungsModulus YoungsModulus::Concrete() {
    static const YoungsModulus concrete(22000);
    return concrete;
}

const YoungsModulus YoungsModulus::Wood() {
    static const YoungsModulus wood(10000);
    return wood;
}
*/
