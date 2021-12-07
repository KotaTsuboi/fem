#pragma once

#include <memory>
#include <vector>

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "node_force_2d.hpp"

class ConcentratedLoad2D : public NodeForce2D {
  public:
    ConcentratedLoad2D(std::shared_ptr<Node> node, Axis2D axis, double value);

    std::shared_ptr<Node> GetNode();

    Axis2D GetAxis();

    double GetValue();

  private:
    std::shared_ptr<Node> node;
    Axis2D axis;
    double value;
};
