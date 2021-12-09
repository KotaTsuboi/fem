#pragma once

#include "../constraint/constraint_2d.hpp"
#include "../constraint/constraint_collection_2d.hpp"
#include "../geometry/point.hpp"
#include "../load/load_collection_2d.hpp"
#include "../mesh/mesh.hpp"
#include "../output/element_data.hpp"
#include "../output/node_data.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/global_stiffness_matrix_2d.hpp"
#include "../util/iterator.hpp"
#include "Eigen/Core"
#include "Eigen/IterativeLinearSolvers"
#include "Eigen/Sparse"

#include <map>
#include <memory>
#include <vector>

class Structure2D {
  public:
    static const int NumDimension;

    Structure2D(std::vector<std::shared_ptr<Node>> nodes, std::shared_ptr<Mesh> mesh);

    void SetLoads(LoadCollection2D loads);

    void SetConstraint(ConstraintCollection2D constraints);

    void Analize();

    ElementData GetStresses();

    NodeData GetDisplacements();

    std::vector<std::shared_ptr<Node>> GetNodes();

    std::shared_ptr<Node> GetNodeAt(Point &point);

    unsigned int NumNodes();

    unsigned int NumElements();

    fem::Iterator<std::shared_ptr<Node>> NodeIterator();

    fem::Iterator<std::shared_ptr<FiniteElement2D>> ElementIterator();

    void RemoveElement(std::shared_ptr<FiniteElement2D> element);

  private:
    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Mesh> mesh;
    LoadCollection2D loads;
    ConstraintCollection2D constraints;
    ElementData stresses;
    NodeData displacements;
    std::map<std::shared_ptr<Node>, std::vector<std::shared_ptr<FiniteElement2D>>> link;
};
