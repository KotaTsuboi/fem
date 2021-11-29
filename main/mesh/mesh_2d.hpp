#pragma once

#include "../element/finite_element_2d.hpp"
#include "../material/material.hpp"
#include "../problem_type/problem_type.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include <vector>

class Mesh2D {
  public:
    static const int NumDimension;

    Mesh2D(std::vector<Node2D> nodes, std::vector<FiniteElement2D *> elements);

    GlobalStiffnessMatrix2D GlobalKMatrix(Material material, ProblemType problem_type);

    std::vector<Node2D> GetNodes();

    int NumNodes();

  private:
    std::vector<Node2D> nodes;
    std::vector<FiniteElement2D *> elements;
};
