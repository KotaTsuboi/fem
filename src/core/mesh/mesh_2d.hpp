#pragma once

#include "../element/finite_element_2d.hpp"
#include "../node/node.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"
#include "mesh.hpp"
#include <memory>
#include <vector>

class Mesh2D : public Mesh {
  public:
    static const int NumDimension;

    Mesh2D(std::vector<std::shared_ptr<FiniteElement2D>> elements);

    GlobalStiffnessMatrix2D GlobalKMatrix(unsigned int node_size, IndexHolder index_holder);

  private:
    std::vector<std::shared_ptr<FiniteElement2D>> elements;
};
