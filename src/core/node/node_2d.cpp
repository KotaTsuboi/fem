#include "node_2d.hpp"

#include <iostream>

Node2D::Node2D()
    : point(0, 0),
      node_index(num_node) {
}

Node2D::Node2D(double x, double y)
    : point(x, y),
      node_index(num_node) {
    num_node++;
}

Node2D::Node2D(Point2D point) {
}

double Node2D::X() const {
    return point.X();
}

double Node2D::Y() const {
    return point.Y();
}

double Node2D::Z() const {
    return 0;
}

int Node2D::Index() const {
    return node_index;
}

int Node2D::num_node = 0;

bool Node2D::operator<(Node2D &aNode) {
    return this->Index() < aNode.Index();
}

