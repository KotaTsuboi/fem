#include "poissons_ratio.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

PoissonsRatio::PoissonsRatio(double nu) : nu(nu) {
    if (nu < -1) {
        cout << "Poisson's ratio is smaller than -1." << endl;
        exit(EXIT_FAILURE);
    }
    if (0.5 < nu) {
        cout << "Poisson's ratio is bigger than 0.5." << endl;
        exit(EXIT_FAILURE);
    }
}

double PoissonsRatio::Value() const {
    return nu;
}

PoissonsRatio::~PoissonsRatio() {
}

/*
const PoissonsRatio PoissonsRatio::Steel() {
    static const PoissonsRatio steel(0.3);
    return steel;
}

const PoissonsRatio PoissonsRatio::Concrete() {
    static const PoissonsRatio concrete(0.2);
    return concrete;
}

const PoissonsRatio PoissonsRatio::Wood() {
    static const PoissonsRatio wood(0.4);
    return wood;
}
*/
