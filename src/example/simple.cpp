#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

#include "../core/element/finite_element_2d.hpp"
#include "../core/element/triangle_element_2d.hpp"
#include "../core/load/concentrated_load_2d.hpp"
#include "../core/material/material.hpp"
#include "../core/material/poissons_ratio.hpp"
#include "../core/material/youngs_modulus.hpp"
#include "../core/mesh/mesh_2d.hpp"
#include "../core/node/node_2d.hpp"
#include "../core/problem_type/problem_type.hpp"
#include "../core/structure/structure_2d.hpp"
#include "../core/vtk/vtu_writer.hpp"

#include <memory>

using std::cout;
using std::endl;

int main() {
    std::shared_ptr<Node> n1(new Node2D(0, 1000));
    std::shared_ptr<Node> n2(new Node2D(1000, 1000));
    std::shared_ptr<Node> n3(new Node2D(0, 0));
    std::shared_ptr<Node> n4(new Node2D(1000, 0));

    std::vector<std::shared_ptr<Node>> nodes = {n1, n2, n3, n4};

    std::shared_ptr<FiniteElement2D> element1(new TriangleElement2D(n1, n3, n2));
    std::shared_ptr<FiniteElement2D> element2(new TriangleElement2D(n2, n3, n4));

    std::vector<std::shared_ptr<FiniteElement2D>> element_list = {
        element1,
        element2,
    };

    Mesh2D mesh(nodes, element_list);

    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(205000));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    Material material = Material(*e, *nu);

    ProblemType problem_type = ProblemType::PlaneStrain;

    Structure2D structure(mesh, material, problem_type);

    Load2D *p = new ConcentratedLoad2D(0, -1000, n2);
    std::vector<Load2D *> load_list = {p};
    LoadCollection2D loads(load_list);
    structure.SetLoads(loads);

    Constraint2D constraint1(n1, Axis2D::X);
    Constraint2D constraint2(n1, Axis2D::Y);
    Constraint2D constraint3(n3, Axis2D::X);
    Constraint2D constraint4(n3, Axis2D::Y);
    std::vector<Constraint2D> constraint_list = {
        constraint1,
        constraint2,
        constraint3,
        constraint4,
    };
    ConstraintCollection2D constraints(constraint_list);
    structure.SetConstraint(constraints);

    map<std::shared_ptr<Node>, map<Axis2D, double>> displacement = structure.Analize();

    for (auto node : nodes) {
        double dx = displacement[node][Axis2D::X];
        double dy = displacement[node][Axis2D::Y];

        cout << node->X() + dx << ", " << node->Y() + dy << endl;
    }

    return EXIT_SUCCESS;
}
