#pragma once

#include "Eigen/Sparse"
#include "finite_element_2d.hpp"
#include "global_stiffness_matrix_2d.hpp"
#include "material.hpp"
#include "problem_type.hpp"
#include "vector_util.hpp"
#include <vector>

using namespace std;

class Mesh2D {
  public:
    static const int NumDimension;

    Mesh2D(vector<Node2D> nodes, vector<FiniteElement2D *> elements)
        : nodes(nodes),
          elements(elements) {
    }
    GlobalStiffnessMatrix2D GlobalKMatrix(Material material, ProblemType problem_type) {
        vector<int> node_indexes;
        for (Node2D &node : nodes) {
            node_indexes.push_back(node.Index());
        }

        GlobalStiffnessMatrix2D global_k_matrix(nodes);

        for (FiniteElement2D *element : elements) {
            Eigen::MatrixXd element_k_matrix = element->KMatrix(material, problem_type);

            for (int i = 0; i < element->NumNode(); i++) {
                for (int j = 0; j < element->NumNode(); j++) {
                    Node2D node_i = element->GetNode(i);
                    Node2D node_j = element->GetNode(j);

                    for (auto axis_i : Axis2D()) {
                        for (auto axis_j : Axis2D()) {
                            int d_i = underlying_type<Axis2D>::type(axis_i);
                            int d_j = underlying_type<Axis2D>::type(axis_j);

                            double value = element_k_matrix(NumDimension * i + d_i, NumDimension * j + d_j);

                            global_k_matrix.add(node_i, axis_i, node_j, axis_j, value);
                        }
                    }
                }
            }
        }

        global_k_matrix.makeMatrix();

        return global_k_matrix;
    }

    vector<Node2D> GetNodes() {
        return nodes;
    }

    int NumNodes() {
        return nodes.size();
    }

  private:
    vector<Node2D> nodes;
    vector<FiniteElement2D *> elements;
};

const int Mesh2D::NumDimension = 2;
