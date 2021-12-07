#include "poissons_ratio.hpp"
#include <cassert>

PoissonsRatio::PoissonsRatio(double nu) : nu(nu) {
    assert(nu > -1 && "Poisson's ratio must be greater than -1");
    assert(nu < 0.5 && "Poisson's ratio must be less than 0.5");
}

double PoissonsRatio::Value() const {
    return nu;
}
