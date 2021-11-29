#pragma once

class YoungsModulus {
  public:
    static const YoungsModulus Steel();
    static const YoungsModulus Concrete();
    static const YoungsModulus Wood();

    YoungsModulus(const double e);

    double E();

  private:
    const double e;
};
