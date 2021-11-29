#include "material.hpp"
#include "../problem_type/problem_type.hpp"
#include "Eigen/Core"
#include "poissons_ratio.hpp"
#include "youngs_modulus.hpp"
#include <iostream>

#include <math.h>

Material::Material(YoungsModulus youngs_modulus, PoissonsRatio poissons_ratio)
    : youngs_modulus(youngs_modulus),
      poissons_ratio(poissons_ratio),
      d_matrix(3, 3) {
}

Eigen::MatrixXd Material::DMatrix(ProblemType problem_type) {
    double nu = poissons_ratio.Nu();
    double e = youngs_modulus.E();
    std::cout << "E: " << e << std::endl;
    std::cout << "nu: " << nu << std::endl;

    if (problem_type == ProblemType::PlaneStress) {
        std::cout << "plane stress" << std::endl;
        d_matrix << 1, nu, 0,
            nu, 1, 0,
            0, 0, (1 - nu) / 2;
        d_matrix *= e / (1 - pow(nu, 2));
    } else if (problem_type == ProblemType::PlaneStrain) {
        std::cout << "plane strain" << std::endl;
        d_matrix << 1, nu / (1 - nu), 0,
            nu / (1 - nu), 1, 0,
            0, 0, (1 - 2 * nu) / 2 / (1 - nu);
        d_matrix *= (1 - nu) * e / (1 + nu) / (1 - 2 * nu);
    }

    std::cout << "D Matrix: " << d_matrix << std::endl;

    return d_matrix;
}

const Material Material::Steel() {
    static const Material steel(YoungsModulus::Steel(), PoissonsRatio::Steel());
    return steel;
}

const Material Material::Concrete() {
    static const Material concrete(YoungsModulus::Concrete(), PoissonsRatio::Concrete());
    return concrete;
}

const Material Material::Wood() {
    static const Material wood(YoungsModulus::Wood(), PoissonsRatio::Wood());
    return wood;
}
