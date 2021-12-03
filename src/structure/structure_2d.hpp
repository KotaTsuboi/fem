#pragma once

#include "../constraint/constraint_2d.hpp"
#include "../constraint/constraint_collection_2d.hpp"
#include "../load/load_collection_2d.hpp"
#include "../material/material.hpp"
#include "../mesh/mesh_2d.hpp"
#include "../problem_type/problem_type.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "Eigen/Core"
#include "Eigen/IterativeLinearSolvers"
#include "Eigen/Sparse"

#include <memory>

class Structure2D {
  public:
    static const int NumDimension;

    Structure2D(Mesh2D mesh, Material material, ProblemType problem_type);

    void SetLoads(LoadCollection2D loads);

    void SetConstraint(ConstraintCollection2D constraints);

    map<std::shared_ptr<Node>, map<Axis2D, double>> Analize();

  private:
    Mesh2D mesh;
    Material material;
    ProblemType problem_type;
    LoadCollection2D loads;
    ConstraintCollection2D constraints;
};
