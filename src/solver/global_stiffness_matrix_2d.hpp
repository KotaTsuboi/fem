#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "Eigen/Core"
#include "Eigen/Sparse"
#include <map>
#include <memory>
#include <vector>

using std::map;

typedef Eigen::Triplet<double> T;

class GlobalStiffnessMatrix2D {

  public:
    GlobalStiffnessMatrix2D(std::vector<std::shared_ptr<Node>> nodes);

    void add(std::shared_ptr<Node> node_i, Axis2D axis_i, std::shared_ptr<Node> node_j, Axis2D axis_j, double value);

    void makeMatrix();

    int index(std::shared_ptr<Node> node, Axis2D axis);

    /*
        Eigen::SparseSymmetricPermutationProduct<Eigen::SparseMatrix<double>, Eigen::Upper | Eigen::Lower> twistedBy(const Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm);
        */

    int rows();

    int cols();

    Eigen::SparseMatrix<double> getEigen();

  private:
    static const int NumDimension;
    map<std::shared_ptr<Node>, map<Axis2D, unsigned int>> index_map;
    Eigen::SparseMatrix<double> matrix;
    std::vector<T> triplet_list;
};
