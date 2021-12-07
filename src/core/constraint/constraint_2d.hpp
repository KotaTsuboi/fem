#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"
#include <memory>

class Constraint2D {
  public:
    Constraint2D(std::shared_ptr<Node> node, Axis2D axis);

    std::shared_ptr<Node> GetNode();

    Axis2D GetAxis();

  private:
    static const int NumDimension;
    std::shared_ptr<Node> node;
    Axis2D axis;
};
