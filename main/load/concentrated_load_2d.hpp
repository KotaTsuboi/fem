#pragma once

#include <vector>

#include "../axis/axis_2d.hpp"
#include "../node/node_2d.hpp"
#include "../solver/force_vector_2d.hpp"
#include "load_2d.hpp"

class ConcentratedLoad2D : public Load2D {
  public:
    ConcentratedLoad2D();

    ConcentratedLoad2D(double px, double py, Node2D position);

    void FillForce(ForceVector2D &f);

  private:
    std::vector<double> value;
    Node2D position;
};
