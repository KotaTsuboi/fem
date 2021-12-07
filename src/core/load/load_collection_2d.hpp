#pragma once

#include <memory>
#include <vector>

#include "../solver/index_holder.hpp"
#include "../node/node.hpp"
#include "node_force_2d.hpp"

class LoadCollection2D {
  public:
    static const int NumDimension;
    LoadCollection2D();

    LoadCollection2D(std::vector<std::shared_ptr<NodeForce2D>> loads);

    ForceVector2D ForceVector(unsigned int node_size, IndexHolder index_holder);

  private:
    std::vector<std::shared_ptr<NodeForce2D>> loads;
};
