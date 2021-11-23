#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

#include "../load/concentrated_load_2d.hpp"
#include "../element/finite_element_2d.hpp"
#include "../material/material.hpp"
#include "../mesh/mesh_2d.hpp"
#include "../node/node_2d.hpp"
#include "../problem_type/problem_type.hpp"
#include "../structure/structure_2d.hpp"
#include "../element/triangle_element_2d.hpp"
#include "../vtk/vtu_writer.hpp"

using namespace std;

int main() {
    Node2D n1(0, 1000);
    Node2D n2(0, 0);
    Node2D n3(500, 500);
    Node2D n4(1000, 1000);
    Node2D n5(1000, 0);
    Node2D n6(2000, 1000);

    vector<Node2D> nodes = {n1, n2, n3, n4, n5, n6};

    TriangleElement2D *element1 = new TriangleElement2D(n1, n2, n3);
    TriangleElement2D *element2 = new TriangleElement2D(n3, n4, n1);
    TriangleElement2D *element3 = new TriangleElement2D(n2, n5, n3);
    TriangleElement2D *element4 = new TriangleElement2D(n3, n5, n4);
    TriangleElement2D *element5 = new TriangleElement2D(n4, n5, n6);

    vector<FiniteElement2D *> element_list = {
        element1,
        element2,
        element3,
        element4,
        element5,
    };

    Mesh2D mesh(nodes, element_list);
    Material material = Material::Steel;
    ProblemType problem_type = ProblemType::PlaneStrain;

    Structure2D structure(mesh, material, problem_type);

    Load2D *p = new ConcentratedLoad2D(0, -1000e3, n6);
    vector<Load2D *> load_list = {p};
    LoadCollection2D loads(load_list);
    structure.SetLoads(loads);

    Constraint2D constraint1(n1, Axis2D::X);
    Constraint2D constraint2(n1, Axis2D::Y);
    Constraint2D constraint3(n2, Axis2D::X);
    Constraint2D constraint4(n2, Axis2D::Y);
    vector<Constraint2D> constraint_list = {
        constraint1,
        constraint2,
        constraint3,
        constraint4,
    };
    ConstraintCollection2D constraints(constraint_list);
    structure.SetConstraint(constraints);

    map<Node2D, map<Axis2D, double>> displacement = structure.Analize();

    for (auto node : nodes) {
        for (auto axis : Axis2D()) {
            cout << "n" << node.Index() << ", " << axis << ":"
            << displacement[node][axis] << endl;
        }
    }

    vector<vector<double>> coordinates_before;

    for (auto node : nodes) {
        vector<double> coord = {node.X(), node.Y(), 0};
        coordinates_before.push_back(coord);
    }

    vector<vector<double>> coordinates_after;

    for (auto node : nodes) {
        double dx = displacement[node][Axis2D::X];
        double dy = displacement[node][Axis2D::Y];

        vector<double> coord = {node.X() + dx, node.Y() + dy, 0};
        cout << node.X() + dx << ", " << node.Y() + dy << endl;
        coordinates_after.push_back(coord);
    }

    VtuWriter writer_before(coordinates_before);
    writer_before.write("fem_test_before.vtu", false);

    VtuWriter writer_after(coordinates_after);
    writer_after.write("fem_test_after.vtu", false);

    /*
    Node2D n1(0, 1000);
    Node2D n2(1000, 1000);
    Node2D n3(0, 0);
    Node2D n4(1000, 0);

    vector<Node2D> nodes = {n1, n2, n3, n4};

    TriangleElement2D *element1 = new TriangleElement2D(n1, n3, n2);
    TriangleElement2D *element2 = new TriangleElement2D(n2, n3, n4);

    vector<FiniteElement2D *> element_list = {
        element1,
        element2,
    };

    Mesh2D mesh(nodes, element_list);
    Material material = Material::Steel;
    ProblemType problem_type = ProblemType::PlaneStrain;

    Structure2D structure(mesh, material, problem_type);

    Load2D *p = new ConcentratedLoad2D(0, -1000, n2);
    vector<Load2D *> load_list = {p};
    LoadCollection2D loads(load_list);
    structure.SetLoads(loads);

    Constraint2D constraint1(n1, Axis2D::X);
    Constraint2D constraint2(n1, Axis2D::Y);
    Constraint2D constraint3(n3, Axis2D::X);
    Constraint2D constraint4(n3, Axis2D::Y);
    vector<Constraint2D> constraint_list = {
        constraint1,
        constraint2,
        constraint3,
        constraint4,
    };
    ConstraintCollection2D constraints(constraint_list);
    structure.SetConstraint(constraints);

    structure.Analize();
    */

    return EXIT_SUCCESS;
}
