#pragma once

#include "Eigen/Core"

#include "../material/material.hpp"
#include "../node/node_2d.hpp"
#include "finite_element_2d.hpp"
#include <vector>

class TriangleElement2D : public FiniteElement2D {
  public:
    TriangleElement2D(Node2D n1, Node2D n2, Node2D n3);

    Eigen::MatrixXd BMatrix();

    Eigen::MatrixXd KMatrix(Material material, ProblemType problem_type);

    int NumNode();

    double Area();

    Node2D GetNode(int i);

    int GlobalNodeIndex(int i);

  private:
    std::vector<Node2D> nodes;
    const int num_node;
    const double area;
    Eigen::MatrixXd b_matrix;
    Eigen::MatrixXd k_matrix;
};
