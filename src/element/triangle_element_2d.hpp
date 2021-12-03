#pragma once

#include "Eigen/Core"

#include "../material/material.hpp"
#include "../node/node.hpp"
#include "finite_element_2d.hpp"
#include <vector>
#include <memory>

class TriangleElement2D : public FiniteElement2D {
  public:
    TriangleElement2D(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::shared_ptr<Node> n3);

    Eigen::MatrixXd BMatrix();

    Eigen::MatrixXd KMatrix(Material material, ProblemType problem_type);

    int NumNode();

    double Area();

    std::shared_ptr<Node> GetNode(int i);

    // int GlobalNodeIndex(int i);

    ~TriangleElement2D();

  private:
    // std::vector<Node *> nodes;
    std::shared_ptr<Node> n1;
    std::shared_ptr<Node> n2;
    std::shared_ptr<Node> n3;
    const int num_node;
    const double area;
    Eigen::MatrixXd b_matrix;
    Eigen::MatrixXd k_matrix;
};
