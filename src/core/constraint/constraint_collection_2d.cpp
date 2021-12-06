#include "constraint_collection_2d.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../util/vector_util.hpp"
#include "Eigen/Core"
#include "constraint_2d.hpp"
#include <vector>
#include <memory>

ConstraintCollection2D::ConstraintCollection2D()
    : constraint_list() {
}

ConstraintCollection2D::ConstraintCollection2D(std::vector<Constraint2D> constraint_list)
    : constraint_list(constraint_list) {
}

Eigen::SparseMatrix<double> ConstraintCollection2D::ContractSparseMatrix(GlobalStiffnessMatrix2D m) {
    std::vector<int> constraint_indexes;

    for (Constraint2D constraint : constraint_list) {
        constraint_indexes.push_back(constraint.GetIndex(m));
    }

    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm = CreatePermutationMatrix(m.rows(), constraint_indexes);

    Eigen::SparseMatrix<double> m_perm = perm.inverse() * m.getEigen() * perm;

    int n_sub = m.rows() - constraint_list.size();

    Eigen::SparseMatrix<double> m_sub(n_sub, n_sub);
    m_sub = m_perm.topLeftCorner(n_sub, n_sub);

    return m_sub;
}

Eigen::VectorXd ConstraintCollection2D::ContractVector(ForceVector2D v) {
    std::vector<int> constraint_indexes;

    for (Constraint2D constraint : constraint_list) {
        constraint_indexes.push_back(constraint.GetIndex(v));
    }

    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm = CreatePermutationMatrix(v.size(), constraint_indexes);

    Eigen::VectorXd v_perm = perm.inverse() * v.getEigen();

    int n_sub = v.size() - constraint_list.size();

    Eigen::VectorXd v_sub(n_sub);
    v_sub = v_perm.head(n_sub);

    return v_sub;
}

map<std::shared_ptr<Node>, map<Axis2D, double>> ConstraintCollection2D::Displacement() {
    map<std::shared_ptr<Node>, map<Axis2D, double>> displacement;
    for (auto constraint : constraint_list) {
        constraint.FillMap(displacement);
    }
    return displacement;
}

Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> ConstraintCollection2D::CreatePermutationMatrix(int n, std::vector<int> constraint_indexes) {
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
