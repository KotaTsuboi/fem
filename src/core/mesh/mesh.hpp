#pragma once

#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"

class Mesh {
  public:
    virtual GlobalStiffnessMatrix2D GlobalKMatrix(unsigned int node_size, IndexHolder index_holder) = 0;
    virtual ~Mesh() = default;
};
