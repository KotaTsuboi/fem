#pragma once

class MaterialConstant {
  public:
    virtual double Value() const = 0;
    virtual ~MaterialConstant() = default;
};
