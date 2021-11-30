#pragma once

#include "material_constant.hpp"

class YoungsModulus : public MaterialConstant {
  public:
    //static const YoungsModulus Steel();
    //static const YoungsModulus Concrete();
    //static const YoungsModulus Wood();

    YoungsModulus(const double e);

    double Value() const;

    ~YoungsModulus();

  private:
    const double e;
};
