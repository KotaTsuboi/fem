#pragma once

#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "Eigen/Core"
#include "constraint_2d.hpp"
#include <vector>
#include <memory>

class ConstraintCollection2D {
  public:
    ConstraintCollection2D();

    ConstraintCollection2D(std::vector<Constraint2D> constraint_list);

    Eigen::SparseMatrix<double> ContractSparseMatrix(GlobalStiffnessMatrix2D m);

    Eigen::VectorXd ContractVector(ForceVector2D v);

    map<std::shared_ptr<Node>, map<Axis2D, double>> Displacement();

  private:
    std::vector<Constraint2D> constraint_list;

    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> CreatePermutationMatrix(int n, std::vector<int> constraint_indexes);
};
