#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include <map>
#include <vector>

using std::map;

class ForceVector2D {
  public:
    ForceVector2D(std::vector<Node2D> nodes);

    void add(Node2D node, Axis2D axis, double value);

    int index(Node2D node, Axis2D axis);

    int size();

    Eigen::VectorXd getEigen();

  private:
    static const int NumDimension;
    Eigen::VectorXd vector;
    map<Node2D, map<Axis2D, unsigned int>> index_map;
};
