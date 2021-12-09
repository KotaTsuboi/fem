#pragma once

#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"
#include "../output/node_data.hpp"
#include "Eigen/Core"
#include "constraint_2d.hpp"
#include <memory>
#include <vector>

class ConstraintCollection2D {
  public:
    ConstraintCollection2D();

    ConstraintCollection2D(std::vector<Constraint2D> constraint_list);

    std::vector<int> ConstraintIndexes(IndexHolder index_holder);

    NodeData Displacement();

  private:
    std::vector<Constraint2D> constraint_list;
};
