#include "constraint_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

Constraint2D::Constraint2D(std::shared_ptr<Node> node, Axis2D axis)
    : node(node),
      axis(axis) {
}

std::shared_ptr<Node> Constraint2D::GetNode() {
    return node;
}

Axis2D Constraint2D::GetAxis() {
    return axis;
}

const int Constraint2D::NumDimension = 2;
