#pragma once

#include "Eigen/Core"
#include "poissons_ratio.hpp"
#include "problem_type.hpp"
#include "youngs_modulus.hpp"

#include <math.h>

class Material {
  public:
    static const Material Steel;
    static const Material Concrete;
    static const Material Wood;

    Material(YoungsModulus youngs_modulus, PoissonsRatio poissons_ratio)
        : youngs_modulus(youngs_modulus),
          poissons_ratio(poissons_ratio),
          d_matrix(3, 3) {
    }

    Eigen::MatrixXd DMatrix(ProblemType problem_type) {
        double nu = poissons_ratio.Nu();
        double e = youngs_modulus.E();

        if (problem_type == ProblemType::PlaneStress) {
            d_matrix << 1, nu, 0,
                nu, 1, 0,
                0, 0, (1 - nu) / 2;
            d_matrix *= e / (1 - pow(nu, 2));
        } else if (problem_type == ProblemType::PlaneStrain) {
            d_matrix << 1, nu / (1 - nu), 0,
                nu / (1 - nu), 1, 0,
                0, 0, (1 - 2 * nu) / 2 / (1 - nu);
            d_matrix *= (1 - nu) * e / (1 + nu) / (1 - 2 * nu);
        }

        return d_matrix;
    }

  private:
    YoungsModulus youngs_modulus;
    PoissonsRatio poissons_ratio;
    Eigen::MatrixXd d_matrix;
};

const Material Material::Steel = Material(YoungsModulus::Steel, PoissonsRatio::Steel);
const Material Material::Concrete = Material(YoungsModulus::Concrete, PoissonsRatio::Concrete);
const Material Material::Wood = Material(YoungsModulus::Wood, PoissonsRatio::Wood);
