#pragma once

#include "Eigen/Core"
#include "material.hpp"
#include "material_constant.hpp"

class PlaneStrainMaterial : public Material {
  public:
    PlaneStrainMaterial(const MaterialConstant &youngs_modulus, const MaterialConstant &poissons_ratio);

    Eigen::MatrixXd DMatrix();

  private:
    Eigen::MatrixXd d_matrix;
    const MaterialConstant &youngs_modulus;
    const MaterialConstant &poissons_ratio;
};
