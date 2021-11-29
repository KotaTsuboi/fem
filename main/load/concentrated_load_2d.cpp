#include "concentrated_load_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "../solver/force_vector_2d.hpp"
#include "load_2d.hpp"

using std::underlying_type;

ConcentratedLoad2D::ConcentratedLoad2D()
    : value({0, 0}),
      position(Node2D()) {
}

ConcentratedLoad2D::ConcentratedLoad2D(double px, double py, Node2D position)
    : value({px, py}),
      position(position) {
}

void ConcentratedLoad2D::FillForce(ForceVector2D &f) {
    for (auto axis : Axis2D()) {
        int d = underlying_type<Axis2D>::type(axis);
        f.add(position, axis, value[d]);
    }
}