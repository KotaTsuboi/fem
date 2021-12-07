#pragma once

#include "material_constant.hpp"

class YoungsModulus : public MaterialConstant {
  public:
    YoungsModulus(const double e);

    double Value() const;

    ~YoungsModulus() = default;

  private:
    const double e;
};
