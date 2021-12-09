#pragma once

#include <map>
#include <memory>

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"

class NodeData {
  public:
    void SetValue(std::shared_ptr<Node> node, Axis2D axis, double value);

    double ValueOf(std::shared_ptr<Node> node, Axis2D axis);

    bool HasValue(std::shared_ptr<Node> node, Axis2D axis);

  private:
    std::map<std::shared_ptr<Node>, std::map<Axis2D, double>> map;
};
