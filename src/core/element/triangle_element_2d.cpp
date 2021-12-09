#include "Eigen/Core"

#include "../material/material.hpp"
#include "../node/node.hpp"
#include "finite_element_2d.hpp"
#include "triangle_element_2d.hpp"

#include <memory>

TriangleElement2D::TriangleElement2D(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::shared_ptr<Node> n3, Material &material)
    : nodes({n1, n2, n3}),
      material(material),
      num_node(3),
      area((n1->X() * n2->Y() + n2->X() * n3->Y() + n3->X() * n1->Y() - n1->X() * n3->Y() - n2->X() * n1->Y() - n3->X() * n2->Y()) / 2),
      b_matrix(3, 6),
      k_matrix(6, 6) {
    assert(area >= 0);
}

Eigen::MatrixXd TriangleElement2D::BMatrix() {
    double x1 = nodes[0]->X();
    double x2 = nodes[1]->X();
    double x3 = nodes[2]->X();

    double y1 = nodes[0]->Y();
    double y2 = nodes[1]->Y();
    double y3 = nodes[2]->Y();

    double z1 = nodes[0]->Z();
    double z2 = nodes[1]->Z();
    double z3 = nodes[2]->Z();

    b_matrix << y2 - y3, 0, y3 - y1, 0, y1 - y2, 0,
        0, x3 - x2, 0, x1 - x3, 0, x2 - x1,
        x3 - x2, y2 - y3, x1 - x3, y3 - y1, x2 - x1, y1 - y2;

    b_matrix /= 2 * area;

    return b_matrix;
}

Eigen::MatrixXd TriangleElement2D::KMatrix() {
    Eigen::MatrixXd b_matrix = BMatrix();
    Eigen::MatrixXd d_matrix = DMatrix();
    k_matrix = b_matrix.transpose() * d_matrix * b_matrix;
    k_matrix *= area;
    return k_matrix;
}

Eigen::MatrixXd TriangleElement2D::DMatrix() {
    return material.DMatrix();
}

int TriangleElement2D::NumNode() {
    return num_node;
}

double TriangleElement2D::Area() {
    return area;
}

std::shared_ptr<Node> TriangleElement2D::GetNode(int i) {
    return nodes[i];
}

fem::Iterator<std::shared_ptr<Node>> TriangleElement2D::Iterator() {
    fem::Iterator<std::shared_ptr<Node>> iterator(nodes);
    return iterator;
}

/*
int TriangleElement2D::GlobalNodeIndex(int i) {
    return nodes[i].Index();
}
*/

TriangleElement2D::~TriangleElement2D() {
}
