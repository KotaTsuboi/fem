#include "Eigen/Core"

#include "../material/material.hpp"
#include "../node/node.hpp"
#include "finite_element_2d.hpp"
#include "triangle_element_2d.hpp"

#include <memory>

TriangleElement2D::TriangleElement2D(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::shared_ptr<Node> n3)
    : n1(n1), n2(n2), n3(n3),
      num_node(3),
      area((n1->X() * n2->Y() + n2->X() * n3->Y() + n3->X() * n1->Y() - n1->X() * n3->Y() - n2->X() * n1->Y() - n3->X() * n2->Y()) / 2),
      b_matrix(3, 6),
      k_matrix(6, 6) {
}

Eigen::MatrixXd TriangleElement2D::BMatrix() {
    /*
    Node &n1 = nodes[0];
    Node &n2 = nodes[1];
    Node &n3 = nodes[2];
    */

    double x1 = n1->X();
    double x2 = n2->X();
    double x3 = n3->X();

    double y1 = n1->Y();
    double y2 = n2->Y();
    double y3 = n3->Y();

    double z1 = n1->Z();
    double z2 = n2->Z();
    double z3 = n3->Z();

    b_matrix << y2 - y3, 0, y3 - y1, 0, y1 - y2, 0,
        0, x3 - x2, 0, x1 - x3, 0, x2 - x1,
        x3 - x2, y2 - y3, x1 - x3, y3 - y1, x2 - x1, y1 - y2;

    b_matrix /= 2 * area;

    return b_matrix;
}

Eigen::MatrixXd TriangleElement2D::KMatrix(Material material, ProblemType problem_type) {
    Eigen::MatrixXd b_matrix = BMatrix();
    Eigen::MatrixXd d_matrix = material.DMatrix(problem_type);
    k_matrix = b_matrix.transpose() * d_matrix * b_matrix;
    k_matrix *= area;
    return k_matrix;
}

int TriangleElement2D::NumNode() {
    return num_node;
}

double TriangleElement2D::Area() {
    return area;
}

std::shared_ptr<Node> TriangleElement2D::GetNode(int i) {
    if (i == 0) {
        return n1;
    }
    if (i == 1) {
        return n2;
    }
    if (i == 2) {
        return n3;
    }

    exit(EXIT_FAILURE);
}

/*
int TriangleElement2D::GlobalNodeIndex(int i) {
    return nodes[i].Index();
}
*/

TriangleElement2D::~TriangleElement2D() {
}
