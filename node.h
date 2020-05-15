#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {
  using value_type = T;
  Node(const value_type& val) : value(val) {}
  value_type value;
};

template<typename NodeType>
struct NodeTraits {
  using node_tag = typename NodeType::node_tag;
};

struct forward_node_tag{};
struct double_node_tag{};
struct circular_node_tag{};
struct circular_double_node_tag{};

template<typename T>
struct ForwardNode : public Node<T> {
  using node_tag = forward_node_tag;
  using value_type = typename Node<T>::value_type;

  ForwardNode(const value_type& val) : Node<T>(val), next(nullptr) {}

  ForwardNode<value_type>* next;
};

template<typename T>
struct DoubleNode : public Node<T> {
  using node_tag = double_node_tag;
  using value_type = typename Node<T>::value_type;

  DoubleNode(const value_type& val) : Node<T>(val), next(nullptr), prev(nullptr) {}

  DoubleNode<value_type>* next;
  DoubleNode<value_type>* prev;
};

template<typename T>
struct CircularNode : public Node<T> {
  using node_tag = circular_node_tag;
  using value_type = typename Node<T>::value_type;

  CircularNode(const value_type& val) : Node<T>(val), next(nullptr) {}

  CircularNode<value_type>* next;
};

template<typename T>
struct CircularDoubleNode : public Node<T> {
  using node_tag = circular_double_node_tag;
  using value_type = typename Node<T>::value_type;

  CircularDoubleNode(const value_type& val) : Node<T>(val), next(nullptr), prev(nullptr) {}

  CircularDoubleNode<value_type>* next;
  CircularDoubleNode<value_type>* prev;
};

#endif
