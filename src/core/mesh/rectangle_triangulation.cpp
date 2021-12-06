#include "rectangle_triangulation.hpp"
#include "../node/node.hpp"
#include "../element/triangle_element_2d.hpp"

#include <memory>
#include <vector>

// for debug
#include <iostream>

RectangleTriangulation::RectangleTriangulation(Rectangle rectangle, int num_x, int num_y)
    : rectangle(rectangle),
    dx(rectangle.Width() / num_x),
    dy(rectangle.Height() / num_y) {
}

std::shared_ptr<Mesh2D> RectangleTriangulation::CreateMesh() {
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::vector<std::shared_ptr<Node>>> node_matrix = NodeMatrix();

    for (auto row : node_matrix) {
        for (auto n : row) {
            nodes.push_back(n);
        }
    }

    std::cout << "Size of nodes: " << nodes.size() << std::endl;

    std::vector<std::shared_ptr<FiniteElement2D>> elements = ElementList(node_matrix);

    std::cout << "Size of elements: " << elements.size() << std::endl;

    std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>(nodes, elements);

    return mesh;
}

std::vector<std::vector<std::shared_ptr<Node>>> RectangleTriangulation::NodeMatrix() {
    std::vector<std::vector<std::shared_ptr<Node>>> coordinates;

    for (double y = rectangle.MinY(); y <= rectangle.MaxY(); y += dy) {
        std::vector<std::shared_ptr<Node>> row;

        for (double x = rectangle.MinX(); x <= rectangle.MaxX(); x += dx) {
            std::shared_ptr<Node> n = std::make_shared<Node2D>(x, y);
            row.push_back(n);
        }

        coordinates.push_back(row);
    }

    return coordinates;
}

std::vector<std::shared_ptr<FiniteElement2D>> RectangleTriangulation::ElementList(std::vector<std::vector<std::shared_ptr<Node>>> node_matrix) {
    std::vector<std::shared_ptr<FiniteElement2D>> elements;

    for (int i = 0; i < node_matrix.size() - 1; i++) {
        for (int j = 0; j < node_matrix[0].size() - 1; j++) {
            std::shared_ptr<Node> n00 = node_matrix[i][j];
            std::shared_ptr<Node> n01 = node_matrix[i + 1][j];
            std::shared_ptr<Node> n10 = node_matrix[i][j + 1];
            std::shared_ptr<Node> n11 = node_matrix[i + 1][j + 1];

            std::shared_ptr<FiniteElement2D> e0 = std::make_shared<TriangleElement2D>(n00, n10, n01);
            std::shared_ptr<FiniteElement2D> e1 = std::make_shared<TriangleElement2D>(n01, n10, n11);

            elements.push_back(e0);
            elements.push_back(e1);
        }
    }

    return elements;
}

