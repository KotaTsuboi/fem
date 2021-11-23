#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

class YoungsModulus {
  public:
    static const YoungsModulus Steel;
    static const YoungsModulus Concrete;
    static const YoungsModulus Wood;

    YoungsModulus(double e) : e(e) {
        if (e < 0) {
            cout << "Young's modulus is smaller than 0." << endl;
            exit(EXIT_FAILURE);
        }
    }

    double E() {
        return e;
    }

  private:
    const double e;
};

const YoungsModulus YoungsModulus::Steel = YoungsModulus(205000);
const YoungsModulus YoungsModulus::Concrete = YoungsModulus(22000);
const YoungsModulus YoungsModulus::Wood = YoungsModulus(10000);
