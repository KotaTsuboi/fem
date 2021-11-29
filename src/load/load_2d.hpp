#pragma once

#include "../solver/force_vector_2d.hpp"

class Load2D {
  public:
    virtual void FillForce(ForceVector2D &f) = 0;

  protected:
    static const int NumDimension;
};
