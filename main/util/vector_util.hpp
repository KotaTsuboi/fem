#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

template <typename T>
int indexof(std::vector<T> vec, const T e) {
    typename std::vector<T>::iterator itr = find(vec.begin(), vec.end(), e);

    if (itr == vec.end()) {
        cout << "Search failed" << endl;
        exit(EXIT_FAILURE);
    }

    return distance(vec.begin(), itr);
}
