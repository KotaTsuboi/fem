#pragma once

#include "Eigen/Core"

class Material {
  public:
    virtual Eigen::MatrixXd DMatrix() = 0;
    virtual ~Material() = default;
};
