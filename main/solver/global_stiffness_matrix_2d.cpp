#include "global_stiffness_matrix_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include "Eigen/Sparse"
#include <map>
#include <vector>

typedef Eigen::Triplet<double> T;

GlobalStiffnessMatrix2D::GlobalStiffnessMatrix2D(std::vector<Node2D> nodes)
    : matrix(nodes.size() * NumDimension, nodes.size() * NumDimension) {
    unsigned int i = 0;

    for (Node2D node : nodes) {
        for (auto axis : Axis2D()) {
            index_map[node][axis] = i;
            i++;
        }
    }
}

void GlobalStiffnessMatrix2D::add(Node2D node_i, Axis2D axis_i, Node2D node_j, Axis2D axis_j, double value) {
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

int GlobalStiffnessMatrix2D::index(Node2D node, Axis2D axis) {
    return index_map[node][axis];
}

/*
    Eigen::SparseSymmetricPermutationProduct<Eigen::SparseMatrix<double>, Eigen::Upper | Eigen::Lower> twistedBy(const Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm) {
        return matrix.twistedBy(perm);
    }
    */

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
