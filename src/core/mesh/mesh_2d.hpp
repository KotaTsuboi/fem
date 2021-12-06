#pragma once

#include "../element/finite_element_2d.hpp"
#include "../material/material.hpp"
#include "../problem_type/problem_type.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../node/node.hpp"
#include "mesh.hpp"
#include <vector>
#include <memory>

class Mesh2D : public Mesh {
  public:
    static const int NumDimension;

    Mesh2D(std::vector<std::shared_ptr<Node>> nodes, std::vector<std::shared_ptr<FiniteElement2D>> elements);

    GlobalStiffnessMatrix2D GlobalKMatrix(Material material, ProblemType problem_type);

    std::vector<std::shared_ptr<Node>> GetNodes();

    std::shared_ptr<Node> GetNodeClosestTo(Point &point);

    int NumNodes();

    ~Mesh2D();

  private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<FiniteElement2D>> elements;
};
