#include <cstdlib>
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
    double w = 2000;
    double h = 100;
    Point2D p1(0, 0);
    Point2D p2(w, h);

    int nx = 200;
    int ny = 10;

    Rectangle rectangle(p1, p2);

    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(205000));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    std::shared_ptr<Material> material = std::make_shared<PlaneStressMaterial>(*e, *nu);

    RectangleTriangulation mesh_factory(rectangle, nx, ny, *material);
    std::shared_ptr<Structure2D> structure = mesh_factory.CreateMesh();

    std::shared_ptr<Node> load_node = structure->GetNodeClosestTo(p2);
    std::shared_ptr<NodeForce2D> load = std::make_shared<ConcentratedLoad2D>(load_node, Axis2D::Y, -1000);
    std::vector<std::shared_ptr<NodeForce2D>> load_list = {load};
    LoadCollection2D loads(load_list);
    structure->SetLoads(loads);

    std::vector<Constraint2D> constraint_list;

    double dy = h / ny;
    double y = 0;

    while (y <= h) {
        Point2D p_constraint(0, y);

        std::shared_ptr<Node> n_constraint = structure->GetNodeClosestTo(p_constraint);

        Constraint2D constraint_x(n_constraint, Axis2D::X);
        Constraint2D constraint_y(n_constraint, Axis2D::Y);
        constraint_list.push_back(constraint_x);
        constraint_list.push_back(constraint_y);

        y += dy;
    }

    ConstraintCollection2D constraints(constraint_list);
    structure->SetConstraint(constraints);

    structure->Analize();

    NodeData displacements = structure->GetDisplacements();

    ElementData stresses = structure->GetStresses();

    VtuWriter writer_before(*structure);
    writer_before.write("fem_test_before.vtu", false);

    VtuWriter writer_after(*structure);
    writer_after.SetDisplacements(displacements);
    writer_after.SetElementData(stresses, "Mises Stress");
    writer_after.write("fem_test_after.vtu", false);

    return EXIT_SUCCESS;
}
