#pragma once

#include "Eigen/Core"
#include "Eigen/Sparse"
#include "axis_2d.hpp"
#include "node_2d.hpp"
#include <map>
#include <vector>

using namespace std;

typedef Eigen::Triplet<double> T;

class GlobalStiffnessMatrix2D {

  public:
    GlobalStiffnessMatrix2D(vector<Node2D> nodes)
        : matrix(nodes.size() * NumDimension, nodes.size() * NumDimension) {
        unsigned int i = 0;

        for (Node2D node : nodes) {
            for (auto axis : Axis2D()) {
                index_map[node][axis] = i;
                i++;
            }
        }
    }

    void add(Node2D node_i, Axis2D axis_i, Node2D node_j, Axis2D axis_j, double value) {
        if (value == 0) {
            return;
        }

        int i = index(node_i, axis_i);
        int j = index(node_j, axis_j);

        triplet_list.push_back(T(i, j, value));
    }

    void makeMatrix() {
        matrix.setFromTriplets(triplet_list.begin(), triplet_list.end());
    }

    int index(Node2D node, Axis2D axis) {
        return index_map[node][axis];
    }

    /*
        Eigen::SparseSymmetricPermutationProduct<Eigen::SparseMatrix<double>, Eigen::Upper | Eigen::Lower> twistedBy(const Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm) {
            return matrix.twistedBy(perm);
        }
        */

    int rows() {
        return matrix.rows();
    }

    int cols() {
        return matrix.cols();
    }

    Eigen::SparseMatrix<double> getEigen() {
        return matrix;
    }

    void print() {
        cout << matrix << endl;
    }

  private:
    static const int NumDimension;
    map<Node2D, map<Axis2D, unsigned int>> index_map;
    Eigen::SparseMatrix<double> matrix;
    vector<T> triplet_list;
};

const int GlobalStiffnessMatrix2D::NumDimension = 2;
