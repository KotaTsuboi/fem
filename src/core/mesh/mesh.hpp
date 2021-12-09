#pragma once

#include "../element/finite_element_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../solver/index_holder.hpp"
#include "../util/iterator.hpp"

class Mesh {
  public:
    virtual GlobalStiffnessMatrix2D GlobalKMatrix(unsigned int node_size, IndexHolder index_holder) = 0;
    virtual fem::Iterator<std::shared_ptr<FiniteElement2D>> Iterator() = 0;
    virtual unsigned int NumElements() = 0;
    virtual ~Mesh() = default;
};
