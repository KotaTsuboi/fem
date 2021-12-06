#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

#include "../core/geometry/point_2d.hpp"
#include "../core/geometry/rectangle.hpp"
#include "../core/element/finite_element_2d.hpp"
#include "../core/element/triangle_element_2d.hpp"
#include "../core/load/concentrated_load_2d.hpp"
#include "../core/material/material.hpp"
#include "../core/material/poissons_ratio.hpp"
#include "../core/material/youngs_modulus.hpp"
#include "../core/mesh/mesh_2d.hpp"
#include "../core/mesh/rectangle_triangulation.hpp"
#include "../core/node/node_2d.hpp"
#include "../core/problem_type/problem_type.hpp"
#include "../core/structure/structure_2d.hpp"
#include "../core/vtk/vtu_writer.hpp"

#include <memory>

using std::cout;
using std::endl;

int main() {
    Point2D p1(0, 0);
    Point2D p2(2000, 100);
    Rectangle rectangle(p1, p2);
    RectangleTriangulation mesh_factory(rectangle, 200, 10);
    std::shared_ptr<Mesh2D> mesh = mesh_factory.CreateMesh();

    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(205000));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    Material material = Material(*e, *nu);

    ProblemType problem_type = ProblemType::PlaneStrain;

    Structure2D structure(*mesh, material, problem_type);

    std::shared_ptr<Node> load_node = mesh->GetNodeClosestTo(p2);
    Load2D *load = new ConcentratedLoad2D(0, -1000, load_node);
    std::vector<Load2D *> load_list = {load};
    LoadCollection2D loads(load_list);
    structure.SetLoads(loads);

    Point2D p3(0, 1000);

    std::shared_ptr<Node> constraint_node1 = mesh->GetNodeClosestTo(p1);
    std::shared_ptr<Node> constraint_node2 = mesh->GetNodeClosestTo(p3);
    Constraint2D constraint1(constraint_node1, Axis2D::X);
    Constraint2D constraint2(constraint_node1, Axis2D::Y);
    Constraint2D constraint3(constraint_node2, Axis2D::X);
    Constraint2D constraint4(constraint_node2, Axis2D::Y);
    std::vector<Constraint2D> constraint_list = {
        constraint1,
        constraint2,
        constraint3,
        constraint4,
    };
    ConstraintCollection2D constraints(constraint_list);
    structure.SetConstraint(constraints);

    map<std::shared_ptr<Node>, map<Axis2D, double>> displacement = structure.Analize();

    /*
        for (auto node : nodes) {
            for (auto axis : Axis2D()) {
                cout << "n" << node->Index() << ", " << axis << ":"
                     << displacement[*node][axis] << endl;
            }
        }
        */

    std::vector<std::vector<double>> coordinates_before;

    for (auto node : mesh->GetNodes()) {
        std::vector<double> coord = {node->X(), node->Y(), 0};
        coordinates_before.push_back(coord);
    }

    std::vector<std::vector<double>> coordinates_after;

    //cout << "Displacements:" << endl;

    for (auto node : mesh->GetNodes()) {
        double dx = displacement[node][Axis2D::X];
        double dy = displacement[node][Axis2D::Y];

        std::vector<double> coord = {node->X() + dx, node->Y() + dy, 0};
        //cout << node->X() + dx << ", " << node->Y() + dy << endl;
        coordinates_after.push_back(coord);
    }

    VtuWriter writer_before(coordinates_before);
    writer_before.write("fem_test_before.vtu", false);

    VtuWriter writer_after(coordinates_after);
    writer_after.write("fem_test_after.vtu", false);

    return EXIT_SUCCESS;
}
