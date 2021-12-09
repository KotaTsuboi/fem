#include "index_holder.hpp"
#include "../util/vector_util.hpp"
#include "eigen_util.hpp"
#include <iostream>

IndexHolder::IndexHolder(std::vector<std::shared_ptr<Node>> nodes) {
    unsigned int i = 0;

    for (auto node : nodes) {
        for (auto axis : Axis2D()) {
            index_map[node][axis] = i;
            i++;
        }
    }
}

IndexHolder::IndexHolder(std::map<std::shared_ptr<Node>, std::map<Axis2D, unsigned int>> index_map)
    : index_map(index_map) {
}

unsigned int IndexHolder::IndexOf(std::shared_ptr<Node> node, Axis2D axis) {
    return index_map[node][axis];
}

IndexHolder IndexHolder::Contract(std::vector<int> constraint_indexes) {
    std::map<std::shared_ptr<Node>, std::map<Axis2D, unsigned int>> contracted_index_map;

    int node_size = index_map.size();

    std::vector<int> permutation = CreatePermutation(node_size * NumDimension, constraint_indexes);

    for (const auto &[node, sub_map] : index_map) {
        for (const auto &[axis, index] : sub_map) {

            int after_index = indexof<int>(permutation, index);


            if (after_index > node_size * NumDimension - constraint_indexes.size()) {
                continue;
            }

            contracted_index_map[node][axis] = after_index;
        }
    }

    IndexHolder contracted_index_holder(contracted_index_map);

    return contracted_index_holder;
}

const int IndexHolder::NumDimension = 2;
