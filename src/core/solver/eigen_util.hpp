#pragma once

#include "../util/vector_util.hpp"
#include "Eigen/Core"

inline Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> CreatePermutationMatrix(int n, std::vector<int> constraint_indexes) {
    std::vector<int> permutation;

    for (int i = 0; i < n; i++) {
        permutation.push_back(i);
    }

    for (int i : constraint_indexes) {
        int position = indexof(permutation, i);
        permutation.erase(permutation.begin() + position);
        permutation.push_back(i);
    }

    Eigen::VectorXi indices(permutation.size());

    for (int i = 0; i < permutation.size(); i++) {
        indices(i) = permutation[i];
    }

    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm(n);
    perm.indices() = indices;

    return perm;
}