#pragma once

#include <vector>
#include <memory>

#include "../axis/axis_2d.hpp"
#include "../node/node.hpp"
#include "../solver/force_vector_2d.hpp"
#include "load_2d.hpp"

class ConcentratedLoad2D : public Load2D {
  public:
    ConcentratedLoad2D();

    ConcentratedLoad2D(double px, double py, std::shared_ptr<Node> position);

    void FillForce(ForceVector2D &f);

  private:
    std::vector<double> value;
    std::shared_ptr<Node> position;
};
