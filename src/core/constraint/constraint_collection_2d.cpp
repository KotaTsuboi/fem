#include "constraint_collection_2d.hpp"
#include "../output/node_data.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"
#include "../util/vector_util.hpp"
#include "Eigen/Core"
#include "constraint_2d.hpp"
#include <memory>
#include <vector>

ConstraintCollection2D::ConstraintCollection2D()
    : constraint_list() {
}

ConstraintCollection2D::ConstraintCollection2D(std::vector<Constraint2D> constraint_list)
    : constraint_list(constraint_list) {
}

std::vector<int> ConstraintCollection2D::ConstraintIndexes(IndexHolder index_holder) {
    std::vector<int> constraint_indexes;

    for (Constraint2D constraint : constraint_list) {
        constraint_indexes.push_back(index_holder.IndexOf(constraint.GetNode(), constraint.GetAxis()));
    }

    return constraint_indexes;
}

NodeData ConstraintCollection2D::Displacement() {
    NodeData displacements;

    for (auto constraint : constraint_list) {
        displacements.SetValue(constraint.GetNode(), constraint.GetAxis(), 0);
    }

    return displacements;
}
