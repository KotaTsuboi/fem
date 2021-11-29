#pragma once

#include "../problem_type/problem_type.hpp"
#include "Eigen/Core"
#include "poissons_ratio.hpp"
#include "youngs_modulus.hpp"

class Material {
  public:
    static const Material Steel();
    static const Material Concrete();
    static const Material Wood();

    Material(YoungsModulus youngs_modulus, PoissonsRatio poissons_ratio);

    Eigen::MatrixXd DMatrix(ProblemType problem_type);

  private:
    YoungsModulus youngs_modulus;
    PoissonsRatio poissons_ratio;
    Eigen::MatrixXd d_matrix;
};
