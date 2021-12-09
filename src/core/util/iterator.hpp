#pragma once

#include <vector>

namespace fem {

template <class T>
class Iterator {
  public:
    Iterator<T>(std::vector<T> list);
    bool HasNext();
    T Next();

  private:
    int i;
    std::vector<T> list;
};

template <class T>
Iterator<T>::Iterator(std::vector<T> list)
    : list(list),
      i(0) {
}

template <class T>
bool Iterator<T>::HasNext() {
    return i < list.size();
}

template <class T>
T Iterator<T>::Next() {
    T item = list[i];
    i++;
    return item;
}

} // namespace fem
