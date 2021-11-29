#pragma once

class PoissonsRatio {
  public:
    static const PoissonsRatio Steel();
    static const PoissonsRatio Concrete();
    static const PoissonsRatio Wood();

    PoissonsRatio(double nu);

    double Nu();

  private:
    const double nu;
};
