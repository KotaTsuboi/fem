#pragma once

#include "../geometry/rectangle.hpp"
#include "mesh_2d.hpp"
#include <vector>
//#include "mesh_factory.hpp"

class RectangleTriangulation {
  public:
    RectangleTriangulation(Rectangle rectangle, int num_x, int num_y);
    std::shared_ptr<Mesh2D> CreateMesh();
    ~RectangleTriangulation() = default;

  private:
    Rectangle rectangle;
    double dx;
    double dy;

    std::vector<std::vector<std::shared_ptr<Node>>> NodeMatrix();
    std::vector<std::shared_ptr<FiniteElement2D>> ElementList(std::vector<std::vector<std::shared_ptr<Node>>> node_matrix);
};
