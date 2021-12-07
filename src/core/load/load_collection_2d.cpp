#include <memory>
#include <vector>

#include "../node/node.hpp"
#include "../solver/force_vector_2d.hpp"
#include "../solver/index_holder.hpp"
#include "load_collection_2d.hpp"
#include "node_force_2d.hpp"

LoadCollection2D::LoadCollection2D()
    : loads() {
}

LoadCollection2D::LoadCollection2D(std::vector<std::shared_ptr<NodeForce2D>> loads)
    : loads(loads) {
}

ForceVector2D LoadCollection2D::ForceVector(unsigned int node_size, IndexHolder index_holder) {
    ForceVector2D f(node_size, index_holder);

    for (auto load : loads) {
        f.add(load->GetNode(), load->GetAxis(), load->GetValue());
    }

    return f;
}

const int LoadCollection2D::NumDimension = 2;
