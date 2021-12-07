#include "Eigen/Core"
#include "material_constant.hpp"
#include "plane_stress_material.hpp"

#include <cmath>

PlaneStressMaterial::PlaneStressMaterial(const MaterialConstant &youngs_modulus, const MaterialConstant &poissons_ratio)
    : youngs_modulus(youngs_modulus),
      poissons_ratio(poissons_ratio),
      d_matrix(3, 3) {
    double nu = poissons_ratio.Value();
    double e = youngs_modulus.Value();

    d_matrix << 1, nu, 0,
        nu, 1, 0,
        0, 0, (1 - nu) / 2;
    d_matrix *= e / (1 - pow(nu, 2));
}

Eigen::MatrixXd PlaneStressMaterial::DMatrix() {
    return d_matrix;
}
