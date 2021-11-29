#include "youngs_modulus.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

YoungsModulus::YoungsModulus(double e) : e(e) {
    if (e < 0) {
        cout << "Young's modulus is smaller than 0." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Constructor called. E:" << e << endl;
}

double YoungsModulus::E() {
    return e;
}

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
