#include "Eigen/Core"
#include <iostream>

#include "finite_element_2d.hpp"
#include "../material/material.hpp"
#include "../node/node_2d.hpp"
#include "../node/node_index.hpp"

using namespace std;

class TriangleElement2D : public FiniteElement2D {
  public:
    TriangleElement2D(Node2D n1, Node2D n2, Node2D n3)
        : nodes({n1, n2, n3}),
          num_node(3),
          area((n1.X() * n2.Y() + n2.X() * n3.Y() + n3.X() * n1.Y() - n1.X() * n3.Y() - n2.X() * n1.Y() - n3.X() * n2.Y()) / 2),
          b_matrix(3, 6),
          k_matrix(6, 6) {
    }

    Eigen::MatrixXd BMatrix() {
        Node2D n1 = nodes[0];
        Node2D n2 = nodes[1];
        Node2D n3 = nodes[2];
        b_matrix << n2.Y() - n3.Y(), 0, n3.Y() - n1.Y(), 0, n1.Y() - n2.Y(), 0,
            0, n3.X() - n2.X(), 0, n1.X() - n3.X(), 0, n2.X() - n1.X(),
            n3.X() - n2.X(), n2.Y() - n3.Y(), n1.X() - n3.X(), n3.Y() - n1.Y(), n2.X() - n1.X(), n1.Y() - n2.Y();
        b_matrix /= 2 * area;
        return b_matrix;
    }

    Eigen::MatrixXd KMatrix(Material material, ProblemType problem_type) {
        Eigen::MatrixXd b_matrix = BMatrix();
        Eigen::MatrixXd d_matrix = material.DMatrix(problem_type);
        k_matrix = b_matrix.transpose() * d_matrix * b_matrix;
        k_matrix *= area;
        return k_matrix;
    }

    int NumNode() {
        return num_node;
    }

    double Area() {
        return area;
    }

    Node2D GetNode(int i) {
        return nodes[i];
    }

    int GlobalNodeIndex(int i) {
        return nodes[i].Index();
    }

  private:
    vector<Node2D> nodes;
    const int num_node;
    const double area;
    Eigen::MatrixXd b_matrix;
    Eigen::MatrixXd k_matrix;
};
