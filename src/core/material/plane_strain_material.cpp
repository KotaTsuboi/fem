#include "Eigen/Core"
#include "material_constant.hpp"
#include "plane_strain_material.hpp"

#include <cmath>

PlaneStrainMaterial::PlaneStrainMaterial(const MaterialConstant &youngs_modulus, const MaterialConstant &poissons_ratio)
    : youngs_modulus(youngs_modulus),
      poissons_ratio(poissons_ratio),
      d_matrix(3, 3) {
    double nu = poissons_ratio.Value();
    double e = youngs_modulus.Value();

    d_matrix << 1, nu / (1 - nu), 0,
        nu / (1 - nu), 1, 0,
        0, 0, (1 - 2 * nu) / 2 / (1 - nu);

    d_matrix *= (1 - nu) * e / (1 + nu) / (1 - 2 * nu);
}

Eigen::MatrixXd PlaneStrainMaterial::DMatrix() {
    return d_matrix;
}
