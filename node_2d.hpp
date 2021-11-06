#pragma once

class Node2D {
  public:
    Node2D() : x(0), y(0), node_index(num_node) {
    }

    Node2D(double x, double y) : x(x), y(y), node_index(num_node) {
        num_node++;
    }

    double X() const {
        return x;
    }

    double Y() const {
        return y;
    }

    int Index() const {
        return node_index;
    }

  private:
    double x;
    double y;
    unsigned int node_index;
    static int num_node;
};

int Node2D::num_node = 0;

bool operator<(const Node2D &lhs, const Node2D &rhs) {
    return lhs.Index() < rhs.Index();
}
