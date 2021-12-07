#pragma once

#include "material_constant.hpp"

class PoissonsRatio : public MaterialConstant {
  public:
    PoissonsRatio(double nu);

    double Value() const;

    ~PoissonsRatio() = default;

  private:
    const double nu;
};
