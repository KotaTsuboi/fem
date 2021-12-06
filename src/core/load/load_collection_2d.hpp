#pragma once

#include <vector>

#include "../node/node.hpp"
#include "load_2d.hpp"

class LoadCollection2D {
  public:
    static const int NumDimension;
    LoadCollection2D();

    LoadCollection2D(std::vector<Load2D *> loads);

    ForceVector2D ForceVector(std::vector<std::shared_ptr<Node>> nodes);

  private:
    std::vector<Load2D *> loads;
};
