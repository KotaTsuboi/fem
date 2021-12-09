#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include <map>
#include <memory>
#include <vector>

class IndexHolder {
  public:
    static const int NumDimension;
    IndexHolder(std::vector<std::shared_ptr<Node>> nodes);
    IndexHolder(std::map<std::shared_ptr<Node>, std::map<Axis2D, unsigned int>> index_map);
    unsigned int IndexOf(std::shared_ptr<Node> node, Axis2D axis);
    IndexHolder Contract(std::vector<int> constraint_indexes);

  private:
    std::map<std::shared_ptr<Node>, std::map<Axis2D, unsigned int>> index_map;
};
