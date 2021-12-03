#pragma once

#include "../material/material.hpp"
#include "../node/node_2d.hpp"
#include "../problem_type/problem_type.hpp"
#include "Eigen/Core"

#include <memory>

class FiniteElement2D {
  public:
    FiniteElement2D();

    virtual Eigen::MatrixXd BMatrix() = 0;

    virtual Eigen::MatrixXd KMatrix(Material material, ProblemType problem_type) = 0;

    virtual int NumNode() = 0;

    virtual double Area() = 0;

    virtual std::shared_ptr<Node> GetNode(int i) = 0;

    // virtual int GlobalNodeIndex(int i) = 0;

    virtual ~FiniteElement2D();
};
