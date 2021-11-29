#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"

class Constraint2D {
  public:
    Constraint2D(Node2D node, Axis2D axis);

    int GetIndex(GlobalStiffnessMatrix2D m) const;

    int GetIndex(ForceVector2D f) const;

    void FillMap(map<Node2D, map<Axis2D, double>> &displacement);

  private:
    static const int NumDimension;
    Node2D node;
    Axis2D axis;
};
