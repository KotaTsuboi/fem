#include <cstdlib>
#include <math.h>
#include <vector>

#include "../core/element/finite_element_2d.hpp"
#include "../core/element/triangle_element_2d.hpp"
#include "../core/load/concentrated_load_2d.hpp"
#include "../core/material/material.hpp"
#include "../core/material/plane_stress_material.hpp"
#include "../core/material/poissons_ratio.hpp"
#include "../core/material/youngs_modulus.hpp"
#include "../core/mesh/mesh_2d.hpp"
#include "../core/node/node_2d.hpp"
#include "../core/structure/structure_2d.hpp"
#include "../core/vtk/vtu_writer.hpp"

#include <memory>

using std::cout;
using std::endl;

int main() {
    // Define nodes
    std::shared_ptr<Node> n1(new Node2D(0, 1000));
    std::shared_ptr<Node> n2(new Node2D(0, 0));
    std::shared_ptr<Node> n3(new Node2D(500, 500));
    std::shared_ptr<Node> n4(new Node2D(1000, 1000));
    std::shared_ptr<Node> n5(new Node2D(1000, 0));
    std::shared_ptr<Node> n6(new Node2D(2000, 1000));

    std::vector<std::shared_ptr<Node>> nodes = {n1, n2, n3, n4, n5, n6};

    // Define material
    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(205000));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    std::shared_ptr<Material> material = std::make_shared<PlaneStressMaterial>(*e, *nu);

    // Define elements
    std::shared_ptr<FiniteElement2D> element1(new TriangleElement2D(n1, n2, n3, *material));
    std::shared_ptr<FiniteElement2D> element2(new TriangleElement2D(n3, n4, n1, *material));
    std::shared_ptr<FiniteElement2D> element3(new TriangleElement2D(n2, n5, n3, *material));
    std::shared_ptr<FiniteElement2D> element4(new TriangleElement2D(n3, n5, n4, *material));
    std::shared_ptr<FiniteElement2D> element5(new TriangleElement2D(n4, n5, n6, *material));

    std::vector<std::shared_ptr<FiniteElement2D>> element_list = {
        element1,
        element2,
        element3,
        element4,
        element5,
    };

    // Create mesh
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh2D>(element_list);

    // Create structure
    Structure2D structure(nodes, mesh);

    // Define load
    std::shared_ptr<NodeForce2D> load = std::make_shared<ConcentratedLoad2D>(n6, Axis2D::Y, -1000e3);
    std::vector<std::shared_ptr<NodeForce2D>> load_list = {load};
    LoadCollection2D loads(load_list);
    structure.SetLoads(loads);

    // Define constraint
    Constraint2D constraint1(n1, Axis2D::X);
    Constraint2D constraint2(n1, Axis2D::Y);
    Constraint2D constraint3(n2, Axis2D::X);
    Constraint2D constraint4(n2, Axis2D::Y);
    std::vector<Constraint2D> constraint_list = {
        constraint1,
        constraint2,
        constraint3,
        constraint4,
    };
    ConstraintCollection2D constraints(constraint_list);
    structure.SetConstraint(constraints);

    // Solve
    structure.Analize();

    // Get output data
    NodeData displacements = structure.GetDisplacements();
    ElementData stresses = structure.GetStresses();

    // Output as VTK
    VtuWriter writer_before(structure);
    writer_before.write("five_elements_0.vtu", false);

    VtuWriter writer_after(structure);
    writer_after.SetDisplacements(displacements);
    writer_after.SetElementData(stresses, "Mises Stress");
    writer_after.write("five_elements_1.vtu", false);

    return EXIT_SUCCESS;
}
