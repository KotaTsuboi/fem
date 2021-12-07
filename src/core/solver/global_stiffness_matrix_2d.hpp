#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "Eigen/Core"
#include "Eigen/Sparse"
#include "index_holder.hpp"
#include <map>
#include <memory>
#include <vector>

using std::map;

typedef Eigen::Triplet<double> T;

class GlobalStiffnessMatrix2D {

  public:
    GlobalStiffnessMatrix2D(unsigned int node_size, IndexHolder index_holder);

    void add(std::shared_ptr<Node> node_i, Axis2D axis_i, std::shared_ptr<Node> node_j, Axis2D axis_j, double value);

    void makeMatrix();

    int index(std::shared_ptr<Node> node, Axis2D axis);

    Eigen::SparseMatrix<double> Contract(std::vector<int> constraint_indexes);

    int rows();

    int cols();

    Eigen::SparseMatrix<double> getEigen();

  private:
    static const int NumDimension;
    IndexHolder index_holder;
    Eigen::SparseMatrix<double> matrix;
    std::vector<T> triplet_list;
};
