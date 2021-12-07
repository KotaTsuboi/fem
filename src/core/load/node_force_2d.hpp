#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include <memory>

class NodeForce2D {
  public:
    virtual std::shared_ptr<Node> GetNode() = 0;
    virtual Axis2D GetAxis() = 0;
    virtual double GetValue() = 0;
    virtual ~NodeForce2D() = default;
};
