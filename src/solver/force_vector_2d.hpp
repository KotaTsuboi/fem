#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "Eigen/Core"
#include <map>
#include <vector>

using std::map;

class ForceVector2D {
  public:
    ForceVector2D(std::vector<std::shared_ptr<Node>> nodes);

    void add(std::shared_ptr<Node> node, Axis2D axis, double value);

    int index(std::shared_ptr<Node> node, Axis2D axis);

    int size();

    Eigen::VectorXd getEigen();

  private:
    static const int NumDimension;
    Eigen::VectorXd vector;
    map<std::shared_ptr<Node>, map<Axis2D, unsigned int>> index_map;
};
