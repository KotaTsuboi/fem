#include <vector>

#include "../node/node_2d.hpp"
#include "load_2d.hpp"
#include "load_collection_2d.hpp"

LoadCollection2D::LoadCollection2D()
    : loads() {
}

LoadCollection2D::LoadCollection2D(std::vector<Load2D *> loads)
    : loads(loads) {
}

ForceVector2D LoadCollection2D::ForceVector(std::vector<Node2D> nodes) {
    ForceVector2D f(nodes);

    for (Load2D *load : loads) {
        load->FillForce(f);
    }

    return f;
}

const int LoadCollection2D::NumDimension = 2;
