#pragma once

#include "../problem_type/problem_type.hpp"
#include "Eigen/Core"
#include "material_constant.hpp"

class Material {
  public:
    //static const Material Steel();
    //static const Material Concrete();
    //static const Material Wood();

    Material(const MaterialConstant &youngs_modulus, const MaterialConstant &poissons_ratio);

    Eigen::MatrixXd DMatrix(ProblemType problem_type);

  private:
    const MaterialConstant &youngs_modulus;
    const MaterialConstant &poissons_ratio;
    Eigen::MatrixXd d_matrix;
};

