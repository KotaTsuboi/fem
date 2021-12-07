#include "force_vector_2d.hpp"
#include "eigen_util.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include <vector>

ForceVector2D::ForceVector2D(unsigned int node_size, IndexHolder index_holder)
    : vector(Eigen::VectorXd::Zero(node_size * NumDimension)),
    index_holder(index_holder) {
}

void ForceVector2D::add(std::shared_ptr<Node> node, Axis2D axis, double value) {
    unsigned i = index(node, axis);
    vector(i) += value;
}

int ForceVector2D::index(std::shared_ptr<Node> node, Axis2D axis) {
    return index_holder.IndexOf(node, axis);
}

Eigen::VectorXd ForceVector2D::Contract(std::vector<int> constraint_indexes) {
    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm = CreatePermutationMatrix(size(), constraint_indexes);

    Eigen::VectorXd v_perm = perm.inverse() * vector;

    int n_sub = size() - constraint_indexes.size();

    Eigen::VectorXd v_sub(n_sub);
    v_sub = v_perm.head(n_sub);

    return v_sub;
}

int ForceVector2D::size() {
    return vector.size();
}

Eigen::VectorXd ForceVector2D::getEigen() {
    return vector;
}

const int ForceVector2D::NumDimension = 2;
