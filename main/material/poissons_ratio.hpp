#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

class PoissonsRatio {
  public:
    static const PoissonsRatio Steel;
    static const PoissonsRatio Concrete;
    static const PoissonsRatio Wood;

    PoissonsRatio(double nu) : nu(nu) {
        if (nu < -1) {
            cout << "Poisson's ratio is smaller than -1." << endl;
            exit(EXIT_FAILURE);
        }
        if (0.5 < nu) {
            cout << "Poisson's ratio is bigger than 0.5." << endl;
            exit(EXIT_FAILURE);
        }
    }

    double Nu() {
        return nu;
    }

  private:
    const double nu;
};

const PoissonsRatio PoissonsRatio::Steel = PoissonsRatio(0.3);
const PoissonsRatio PoissonsRatio::Concrete = PoissonsRatio(0.2);
const PoissonsRatio PoissonsRatio::Wood = PoissonsRatio(0.4);
