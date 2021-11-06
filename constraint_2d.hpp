#pragma once

#include "axis_2d.hpp"
#include "force_vector_2d.hpp"
#include "global_stiffness_matrix_2d.hpp"
#include "node_2d.hpp"

class Constraint2D {
  public:
    Constraint2D(Node2D node, Axis2D axis)
        : node(node),
          axis(axis) {
    }

    int GetIndex(GlobalStiffnessMatrix2D m) const {
        return m.index(node, axis);
    }

    int GetIndex(ForceVector2D f) const {
        return f.index(node, axis);
    }

    void FillMap(map<Node2D, map<Axis2D, double>> &displacement) {
        cout << "n" << node.Index() + 1
        << axis
        << " disp is zero" << endl;
        displacement[node][axis] = 0;
    }

  private:
    static const int NumDimension;
    Node2D node;
    Axis2D axis;
};

const int Constraint2D::NumDimension = 2;
