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

int Constraint2D::GetIndex(GlobalStiffnessMatrix2D m) const {
    return m.index(node, axis);
}

int Constraint2D::GetIndex(ForceVector2D f) const {
    return f.index(node, axis);
}

void Constraint2D::FillMap(map<std::shared_ptr<Node>, map<Axis2D, double>> &displacement) {
    cout << "n" << node->Index() + 1
         << axis
         << " disp is zero" << endl;
    displacement[node][axis] = 0;
}

const int Constraint2D::NumDimension = 2;
