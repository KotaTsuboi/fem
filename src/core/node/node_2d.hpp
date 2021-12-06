#pragma once

#include "../geometry/point_2d.hpp"
#include "node.hpp"

class Node2D : public Node {
  public:
    Node2D();

    Node2D(double x, double y);

    Node2D(Point2D point);

    double X() const;

    double Y() const;

    double Z() const;

    int Index() const;

    bool operator<(Node2D &aNode);

    ~Node2D() = default;

  private:
    Point2D point;
    unsigned int node_index;
    static int num_node;
};

bool operator<(const Node2D &lhs, const Node2D &rhs);

