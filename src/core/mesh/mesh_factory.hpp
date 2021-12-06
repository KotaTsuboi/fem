#pragma once

#include "mesh.hpp"
#include <memory>

class MeshFactory {
  public:
    virtual std::shared_ptr<Mesh> CreateMesh();
    virtual ~MeshFactory();
};
