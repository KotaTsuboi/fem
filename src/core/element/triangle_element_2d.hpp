#pragma once

#include "Eigen/Core"

#include "../material/material.hpp"
#include "../node/node.hpp"
#include "../util/iterator.hpp"
#include "finite_element_2d.hpp"
#include <vector>
#include <memory>

class TriangleElement2D : public FiniteElement2D {
  public:
    TriangleElement2D(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2, std::shared_ptr<Node> n3, Material &material);

    Eigen::MatrixXd BMatrix();

    Eigen::MatrixXd KMatrix();

    Eigen::MatrixXd DMatrix();

    int NumNode();

    double Area();

    std::shared_ptr<Node> GetNode(int i);

    fem::Iterator<std::shared_ptr<Node>> Iterator();

    // int GlobalNodeIndex(int i);

    ~TriangleElement2D();

  private:
    std::vector<std::shared_ptr<Node>> nodes;
    Material &material;
    const int num_node;
    const double area;
    Eigen::MatrixXd b_matrix;
    Eigen::MatrixXd k_matrix;
};
