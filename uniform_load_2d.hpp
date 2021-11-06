#include <vector>

#include "edge_2d.hpp"

using namespace std;

class UniformLoad2D {
  public:
    UniformLoad2D() : wx(0), wy(0), position(Edge2D()) {
    }
    UniformLoad2D(double wx, double wy, Edge2D position) : wx(wx), wy(wy), position(position) {
    }

  private:
    double wx;
    double wy;
    Edge2D position;
};