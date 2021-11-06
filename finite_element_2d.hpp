#pragma once

#include <iostream>
#include <vector>

#include "Eigen/Core"
#include "material.hpp"
#include "node_2d.hpp"
#include "node_index.hpp"
#include "problem_type.hpp"

using namespace std;

class FiniteElement2D {
  public:
    FiniteElement2D() {
    }

    virtual Eigen::MatrixXd BMatrix() = 0;

    virtual Eigen::MatrixXd KMatrix(Material material, ProblemType problem_type) = 0;

    virtual int NumNode() = 0;

    virtual double Area() = 0;

    virtual Node2D GetNode(int i) = 0;

    virtual int GlobalNodeIndex(int i) = 0;
};
