#pragma once

#include "../constraint/constraint_2d.hpp"
#include "../constraint/constraint_collection_2d.hpp"
#include "../geometry/point.hpp"
#include "../load/load_collection_2d.hpp"
#include "../mesh/mesh.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "Eigen/Core"
#include "Eigen/IterativeLinearSolvers"
#include "Eigen/Sparse"

#include <memory>

class Structure2D {
  public:
    static const int NumDimension;

    Structure2D(std::vector<std::shared_ptr<Node>> nodes, std::shared_ptr<Mesh> mesh);

    void SetLoads(LoadCollection2D loads);

    void SetConstraint(ConstraintCollection2D constraints);

    map<std::shared_ptr<Node>, map<Axis2D, double>> Analize();

    std::vector<std::shared_ptr<Node>> GetNodes();

    std::shared_ptr<Node> GetNodeClosestTo(Point &point);

    int NumNodes();

  private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Mesh> mesh;
    LoadCollection2D loads;
    ConstraintCollection2D constraints;
};
