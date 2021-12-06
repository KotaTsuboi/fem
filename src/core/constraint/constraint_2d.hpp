#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include <memory>

class Constraint2D {
  public:
    Constraint2D(std::shared_ptr<Node> node, Axis2D axis);

    int GetIndex(GlobalStiffnessMatrix2D m) const;

    int GetIndex(ForceVector2D f) const;

    void FillMap(map<std::shared_ptr<Node>, map<Axis2D, double>> &displacement);

  private:
    static const int NumDimension;
    std::shared_ptr<Node> node;
    Axis2D axis;
};
