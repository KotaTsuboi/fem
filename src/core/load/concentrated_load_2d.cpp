#include "concentrated_load_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"

#include <memory>

using std::underlying_type;

/*
ConcentratedLoad2D::ConcentratedLoad2D()
    : value({0, 0}),
      position() {
}
*/

ConcentratedLoad2D::ConcentratedLoad2D(std::shared_ptr<Node> node, Axis2D axis, double value)
    : node(node),
      axis(axis),
      value(value) {
}

std::shared_ptr<Node> ConcentratedLoad2D::GetNode() {
    return node;
}

Axis2D ConcentratedLoad2D::GetAxis() {
    return axis;
}

double ConcentratedLoad2D::GetValue() {
    return value;
}
