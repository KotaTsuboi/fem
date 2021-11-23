#pragma once

#include "Eigen/Core"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include <map>

using namespace std;

class ForceVector2D {
  public:
    ForceVector2D(vector<Node2D> nodes)
        : vector(Eigen::VectorXd::Zero(nodes.size() * NumDimension)) {
        unsigned int i = 0;

        for (Node2D node : nodes) {
            for (auto axis : Axis2D()) {
                index_map[node][axis] = i;
                i++;
            }
        }
    }

    void add(Node2D node, Axis2D axis, double value) {
        unsigned i = index(node, axis);
        vector(i) += value;
    }

    int index(Node2D node, Axis2D axis) {
        return index_map[node][axis];
    }

    int size() {
        return vector.size();
    }

    Eigen::VectorXd getEigen() {
        return vector;
    }

  private:
    static const int NumDimension;
    Eigen::VectorXd vector;
    map<Node2D, map<Axis2D, unsigned int>> index_map;
};

const int ForceVector2D::NumDimension = 2;
