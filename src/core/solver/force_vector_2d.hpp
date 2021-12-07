#pragma once

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "Eigen/Core"
#include "index_holder.hpp"
#include <map>
#include <vector>

using std::map;

class ForceVector2D {
  public:
    ForceVector2D(unsigned int node_size, IndexHolder index_holder);

    void add(std::shared_ptr<Node> node, Axis2D axis, double value);

    int index(std::shared_ptr<Node> node, Axis2D axis);

    Eigen::VectorXd Contract(std::vector<int> constraint_indexes);

    int size();

    Eigen::VectorXd getEigen();

  private:
    static const int NumDimension;
    Eigen::VectorXd vector;
    IndexHolder index_holder;
};
