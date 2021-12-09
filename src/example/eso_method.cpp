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

int main() {
    // Define domain
    double w = 1;
    double h = 2.4;

    Point2D p1(0, 0);
    Point2D p2(w, h);

    Rectangle rectangle(p1, p2);

    // Define the number of elements
    int nx = 25;
    int ny = 60;

    // Define Material
    const std::shared_ptr<MaterialConstant> e(new YoungsModulus(100e9));
    const std::shared_ptr<MaterialConstant> nu(new PoissonsRatio(0.3));
    std::shared_ptr<Material> material = std::make_shared<PlaneStressMaterial>(*e, *nu);

    // Create structure
    RectangleTriangulation mesh_factory(rectangle, nx, ny, *material);
    std::shared_ptr<Structure2D> structure = mesh_factory.CreateMesh();

    // Define load
    Point2D p_load(w, h / 2);

    std::cout << "Load at: (" << w << ", " << h / 2 << ")" << std::endl;

    std::shared_ptr<Node> n_load = structure->GetNodeAt(p_load);
    std::shared_ptr<NodeForce2D> load = std::make_shared<ConcentratedLoad2D>(n_load, Axis2D::Y, -800);
    std::vector<std::shared_ptr<NodeForce2D>> load_list = {load};
    LoadCollection2D loads(load_list);
    structure->SetLoads(loads);

    // Output initial state
    VtuWriter writer_before(*structure);
    writer_before.write("eso_method_before.vtu", false);

    // Parameter for ESO method
    const double RR_0 = 0.01;
    const double ER = 0.01;

    double rr_i = RR_0;

    int old_num_elements = structure->NumElements();

    int count = 0;

    while (rr_i <= 1) {
        std::cout << "RR_i: " << rr_i << std::endl;

        while (true) {
            std::cout << "Number of elements: " << structure->NumElements() << std::endl;

            // Define constraint
            std::vector<Constraint2D> constraint_list;

            double dy = h / ny;
            double y = 0;

            while (y <= h) {
                Point2D p_constraint(0, y);

                std::shared_ptr<Node> n_constraint = structure->GetNodeAt(p_constraint);

                if (n_constraint) {
                    Constraint2D constraint_x(n_constraint, Axis2D::X);
                    Constraint2D constraint_y(n_constraint, Axis2D::Y);
                    constraint_list.push_back(constraint_x);
                    constraint_list.push_back(constraint_y);
                }

                y += dy;
            }

            ConstraintCollection2D constraints(constraint_list);
            structure->SetConstraint(constraints);

            // Solve
            structure->Analize();

            // Get output data
            NodeData displacements = structure->GetDisplacements();
            ElementData stresses = structure->GetStresses();

            // Output as VTK
            VtuWriter writer_after(*structure);
            writer_after.SetDisplacements(displacements);
            writer_after.SetElementData(stresses, "Mises Stress");

            char filename[256];
            sprintf(filename, "eso_method_%04d.vtu", count);

            std::string filename_str = string(filename);

            writer_after.write(filename_str, true);

            // Get max stress
            fem::Iterator<std::shared_ptr<FiniteElement2D>> element_iterator = structure->ElementIterator();

            double max_stress = 0;

            while (element_iterator.HasNext()) {
                std::shared_ptr<FiniteElement2D> element = element_iterator.Next();
                double s_e = stresses.ValueOf(element);

                if (s_e > max_stress) {
                    max_stress = s_e;
                }
            }

            std::cout << "Max stress: " << max_stress << std::endl;

            // Remove element
            element_iterator = structure->ElementIterator();

            while (element_iterator.HasNext()) {
                std::shared_ptr<FiniteElement2D> element = element_iterator.Next();
                double s_e = stresses.ValueOf(element);

                if (s_e / max_stress < rr_i) {
                    structure->RemoveElement(element);
                }
            }

            count++;

            if (structure->NumElements() == old_num_elements) {
                break;
            }

            old_num_elements = structure->NumElements();
        }

        rr_i += ER;
    }

    return EXIT_SUCCESS;
}
