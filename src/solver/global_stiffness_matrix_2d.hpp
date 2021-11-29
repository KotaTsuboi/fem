#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include "Eigen/Sparse"
#include <map>
#include <vector>

using std::map;

typedef Eigen::Triplet<double> T;

class GlobalStiffnessMatrix2D {

  public:
    GlobalStiffnessMatrix2D(std::vector<Node2D> nodes);

    void add(Node2D node_i, Axis2D axis_i, Node2D node_j, Axis2D axis_j, double value);

    void makeMatrix();

    int index(Node2D node, Axis2D axis);

    /*
        Eigen::SparseSymmetricPermutationProduct<Eigen::SparseMatrix<double>, Eigen::Upper | Eigen::Lower> twistedBy(const Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm);
        */

    int rows();

    int cols();

    Eigen::SparseMatrix<double> getEigen();

  private:
    static const int NumDimension;
    map<Node2D, map<Axis2D, unsigned int>> index_map;
    Eigen::SparseMatrix<double> matrix;
    std::vector<T> triplet_list;
};
