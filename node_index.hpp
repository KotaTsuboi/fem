#pragma once

#include <cstdlib>
#include <iostream>

using namespace std;

class NodeIndex {
  public:
    NodeIndex(int i)
        : i(i) {
        if (i < 0) {
            cout << "Node index is smaller than zero." << endl;
            exit(EXIT_FAILURE);
        }
    }

    int Value() {
        return i;
    }

  private:
    int i;
};