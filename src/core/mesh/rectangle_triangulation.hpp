#pragma once

#include "../geometry/rectangle.hpp"
#include "../structure/structure_2d.hpp"
#include "../element/finite_element_2d.hpp"
#include <vector>
#include "../material/material.hpp"
#include "../mesh/mesh.hpp"

class RectangleTriangulation {
  public:
    RectangleTriangulation(Rectangle rectangle, int num_x, int num_y, Material &material);
    std::shared_ptr<Structure2D> CreateMesh();
    ~RectangleTriangulation() = default;

  private:
    Rectangle rectangle;
    double dx;
    double dy;
    Material &material;

    std::vector<std::vector<std::shared_ptr<Node>>> NodeMatrix();
    std::vector<std::shared_ptr<FiniteElement2D>> ElementList(std::vector<std::vector<std::shared_ptr<Node>>> node_matrix);
};
