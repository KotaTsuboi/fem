#pragma once

#include "material_constant.hpp"

class PoissonsRatio : public MaterialConstant {
  public:
    //static const PoissonsRatio Steel();
    //static const PoissonsRatio Concrete();
    //static const PoissonsRatio Wood();

    PoissonsRatio(double nu);

    double Value() const;

    ~PoissonsRatio();

  private:
    const double nu;
};
