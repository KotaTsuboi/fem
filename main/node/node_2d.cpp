#include "node_2d.hpp"

Node2D::Node2D()
    : x(0),
      y(0),
      node_index(num_node) {
}

Node2D::Node2D(double x, double y)
    : x(x),
      y(y),
      node_index(num_node) {
    num_node++;
}

double Node2D::X() const {
    return x;
}

double Node2D::Y() const {
    return y;
}

int Node2D::Index() const {
    return node_index;
}

int Node2D::num_node = 0;

bool operator<(const Node2D &lhs, const Node2D &rhs) {
    return lhs.Index() < rhs.Index();
}