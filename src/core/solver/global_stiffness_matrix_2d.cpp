#include "global_stiffness_matrix_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "Eigen/Core"
#include "Eigen/Sparse"
#include "eigen_util.hpp"
#include <map>
#include <memory>
#include <vector>

typedef Eigen::Triplet<double> T;

GlobalStiffnessMatrix2D::GlobalStiffnessMatrix2D(unsigned int node_size, IndexHolder index_holder)
    : matrix(node_size * NumDimension, node_size * NumDimension),
      index_holder(index_holder) {
}

void GlobalStiffnessMatrix2D::add(std::shared_ptr<Node> node_i, Axis2D axis_i, std::shared_ptr<Node> node_j, Axis2D axis_j, double value) {
    if (value == 0) {
        return;
    }

    int i = index(node_i, axis_i);
    int j = index(node_j, axis_j);

    triplet_list.push_back(T(i, j, value));
}

void GlobalStiffnessMatrix2D::makeMatrix() {
    matrix.setFromTriplets(triplet_list.begin(), triplet_list.end());
}

int GlobalStiffnessMatrix2D::index(std::shared_ptr<Node> node, Axis2D axis) {
    return index_holder.IndexOf(node, axis);
}

Eigen::SparseMatrix<double> GlobalStiffnessMatrix2D::Contract(std::vector<int> constraint_indexes) {
    Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm = CreatePermutationMatrix(rows(), constraint_indexes);

    Eigen::SparseMatrix<double> m_perm = perm.inverse() * matrix * perm;

    int n_sub = rows() - constraint_indexes.size();

    Eigen::SparseMatrix<double> m_sub(n_sub, n_sub);
    m_sub = m_perm.topLeftCorner(n_sub, n_sub);

    return m_sub;
}

int GlobalStiffnessMatrix2D::rows() {
    return matrix.rows();
}

int GlobalStiffnessMatrix2D::cols() {
    return matrix.cols();
}

Eigen::SparseMatrix<double> GlobalStiffnessMatrix2D::getEigen() {
    return matrix;
}

const int GlobalStiffnessMatrix2D::NumDimension = 2;
