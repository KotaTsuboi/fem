#include "node_2d.hpp"

class Edge2D {
  public:
    Edge2D() : n1(Node2D()), n2(Node2D()) {
    }
    Edge2D(Node2D n1, Node2D n2) : n1(n1), n2(n2) {
    }

  private:
    Node2D n1;
    Node2D n2;
};