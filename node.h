#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {

  Node(const T val) : value(val) { }
  T value;
  Node<T>* next;
};

#endif
