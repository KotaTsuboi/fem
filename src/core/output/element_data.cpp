#include "element_data.hpp"

void ElementData::SetValue(std::shared_ptr<FiniteElement2D> element, double value) {
    map[element] = value;
}

double ElementData::ValueOf(std::shared_ptr<FiniteElement2D> element) {
    return map[element];
}
