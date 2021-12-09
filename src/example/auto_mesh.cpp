#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

#include "../core/element/finite_element_2d.hpp"
#include "../core/element/triangle_element_2d.hpp"
#include "../core/geometry/point_2d.hpp"
#include "../core/geometry/rectangle.hpp"
#include "../core/load/concentrated_load_2d.hpp"
#include "../core/material/material.hpp"
#include "../core/material/plane_stress_material.hpp"
#include "../core/material/poissons_ratio.hpp"
#include "../core/material/youngs_modulus.hpp"
#include "../core/mesh/mesh_2d.hpp"
#include "../core/mesh_algorithm/rectangle_triangulation.hpp"
#include "../core/node/node_2d.hpp"
#include "../core/structure/structure_2d.hpp"
#include "../core/vtk/vtu_writer.hpp"

#include <memory>

using std::cout;
using std::endl;

int main() {
    Point2D p1(0, 0);
    Point2D p2(2000, 100);
    Rectangle rectangle(p1, p2);

    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(205000));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    std::shared_ptr<Material> material = std::make_shared<PlaneStressMaterial>(*e, *nu);

    RectangleTriangulation mesh_factory(rectangle, 200, 10, *material);
    std::shared_ptr<Structure2D> structure = mesh_factory.CreateMesh();

    std::shared_ptr<Node> load_node = structure->GetNodeClosestTo(p2);
    std::shared_ptr<NodeForce2D> load = std::make_shared<ConcentratedLoad2D>(load_node, Axis2D::Y, -1000);
    std::vector<std::shared_ptr<NodeForce2D>> load_list = {load};
    LoadCollection2D loads(load_list);
    structure->SetLoads(loads);

    Point2D p3(0, 1000);

    std::shared_ptr<Node> constraint_node1 = structure->GetNodeClosestTo(p1);
    std::shared_ptr<Node> constraint_node2 = structure->GetNodeClosestTo(p3);
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
    structure->SetConstraint(constraints);

    structure->Analize();

    NodeData displacements = structure->GetDisplacements();

    /*
        for (auto node : nodes) {
            for (auto axis : Axis2D()) {
                cout << "n" << node->Index() << ", " << axis << ":"
                     << displacement[*node][axis] << endl;
            }
        }
        */

/*
    std::vector<std::vector<double>> coordinates_before;

    for (auto node : structure->GetNodes()) {
        std::vector<double> coord = {node->X(), node->Y(), 0};
        coordinates_before.push_back(coord);
    }

    std::vector<std::vector<double>> coordinates_after;

    // cout << "Displacements:" << endl;

    for (auto node : structure->GetNodes()) {
        double dx = displacements.ValueOf(node, Axis2D::X);
        double dy = displacements.ValueOf(node, Axis2D::Y);

        std::vector<double> coord = {node->X() + dx, node->Y() + dy, 0};
        // cout << node->X() + dx << ", " << node->Y() + dy << endl;
        coordinates_after.push_back(coord);
    }
    */

    VtuWriter writer_before(*structure);
    writer_before.write("fem_test_before.vtu", false);

    VtuWriter writer_after(*structure);
    writer_after.SetDisplacements(displacements);
    writer_after.write("fem_test_after.vtu", false);

    return EXIT_SUCCESS;
}
