#pragma once

#include "../material/material.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include "../util/iterator.hpp"

#include <memory>

class FiniteElement2D {
  public:
    virtual Eigen::MatrixXd BMatrix() = 0;

    virtual Eigen::MatrixXd KMatrix() = 0;

    virtual Eigen::MatrixXd DMatrix() = 0;

    virtual int NumNode() = 0;

    virtual double Area() = 0;

    virtual std::shared_ptr<Node> GetNode(int i) = 0;

    virtual fem::Iterator<std::shared_ptr<Node>> Iterator() = 0;

    // virtual int GlobalNodeIndex(int i) = 0;

    virtual ~FiniteElement2D() = default;
};
