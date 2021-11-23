#include <vector>

#include "../node/node_2d.hpp"
#include "load_2d.hpp"

using namespace std;

class LoadCollection2D {
  public:
    static const int NumDimension;
    LoadCollection2D()
        : loads() {
    }
    LoadCollection2D(vector<Load2D *> loads)
        : loads(loads) {
    }

    ForceVector2D ForceVector(vector<Node2D> nodes) {
        ForceVector2D f(nodes);
        for (Load2D *load : loads) {
            load->FillForce(f);
        }
        return f;
    }

  private:
    vector<Load2D *> loads;
};

const int LoadCollection2D::NumDimension = 2;
