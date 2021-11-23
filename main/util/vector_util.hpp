#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int indexof(vector<T> vec, const T e) {
    typename vector<T>::iterator itr = find(vec.begin(), vec.end(), e);

    if (itr == vec.end()) {
        cout << "Search failed" << endl;
        exit(EXIT_FAILURE);
    }

    return distance(vec.begin(), itr);
}
