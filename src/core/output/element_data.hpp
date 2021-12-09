#pragma once

#include <map>
#include <memory>

#include "../element/finite_element_2d.hpp"

class ElementData {
  public:
    void SetValue(std::shared_ptr<FiniteElement2D> element, double value);

    double ValueOf(std::shared_ptr<FiniteElement2D> element);

    void Erase(std::shared_ptr<FiniteElement2D> element);

  private:
    std::map<std::shared_ptr<FiniteElement2D>, double> map;
};
