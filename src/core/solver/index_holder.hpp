#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include <map>
#include <memory>
#include <vector>

class IndexHolder {
  public:
    IndexHolder(std::vector<std::shared_ptr<Node>> nodes);
    unsigned int IndexOf(std::shared_ptr<Node> node, Axis2D axis);

  private:
    std::map<std::shared_ptr<Node>, std::map<Axis2D, unsigned int>> index_map;
};
