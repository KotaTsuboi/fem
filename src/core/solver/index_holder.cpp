#include "index_holder.hpp"

IndexHolder::IndexHolder(std::vector<std::shared_ptr<Node>> nodes) {
    unsigned int i = 0;

    for (auto node : nodes) {
        for (auto axis : Axis2D()) {
            index_map[node][axis] = i;
            i++;
        }
    }
}

unsigned int IndexHolder::IndexOf(std::shared_ptr<Node> node, Axis2D axis) {
    return index_map[node][axis];
}
