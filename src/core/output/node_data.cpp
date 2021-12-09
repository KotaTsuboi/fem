#include "node_data.hpp"

void NodeData::SetValue(std::shared_ptr<Node> node, Axis2D axis, double value) {
    map[node][axis] = value;
}

double NodeData::ValueOf(std::shared_ptr<Node> node, Axis2D axis) {
    return map[node][axis];
}

bool NodeData::HasValue(std::shared_ptr<Node> node, Axis2D axis) {
    return map[node].count(axis) > 0;
}
