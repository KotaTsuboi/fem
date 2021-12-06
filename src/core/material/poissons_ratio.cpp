#include "poissons_ratio.hpp"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

PoissonsRatio::PoissonsRatio(double nu) : nu(nu) {
    assert(nu > -1 && "Poisson's ratio must be greater than -1");
    assert(nu < 0.5 && "Poisson's ratio must be less than 0.5");
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
