#pragma once

class Point {
  public:
    virtual double X() const = 0;
    virtual double Y() const = 0;
    virtual double Z() const = 0;
    virtual ~Point() = default;
};

