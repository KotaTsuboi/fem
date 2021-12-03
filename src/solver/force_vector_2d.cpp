#include "force_vector_2d.hpp"
#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "Eigen/Core"
#include <vector>

ForceVector2D::ForceVector2D(std::vector<std::shared_ptr<Node>> nodes)
    : vector(Eigen::VectorXd::Zero(nodes.size() * NumDimension)) {
    unsigned int i = 0;

    for (std::shared_ptr<Node> node : nodes) {
        for (auto axis : Axis2D()) {
            index_map[node][axis] = i;
            i++;
        }
    }
}

void ForceVector2D::add(std::shared_ptr<Node> node, Axis2D axis, double value) {
    unsigned i = index(node, axis);
    vector(i) += value;
}

int ForceVector2D::index(std::shared_ptr<Node> node, Axis2D axis) {
    return index_map[node][axis];
}

int ForceVector2D::size() {
    return vector.size();
}

Eigen::VectorXd ForceVector2D::getEigen() {
    return vector;
}

const int ForceVector2D::NumDimension = 2;
