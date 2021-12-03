#pragma once

#include "node.hpp"

class Node2D : public Node {
  public:
    Node2D();

    Node2D(double x, double y);

    double X() const;

    double Y() const;

    double Z() const;

    int Index() const;

    ~Node2D();

  private:
    double x;
    double y;
    unsigned int node_index;
    static int num_node;
};

bool operator<(const Node2D &lhs, const Node2D &rhs);

