#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include <iostream>

template<typename Node> 
class Iterator {
  public:
	using value_type = typename Node::value_type;

	Iterator() : current(nullptr) {}
	Iterator(Node *node) : current(node) {}

	bool operator!=(const Iterator& other) {
	  return this->current != other.current;
	}

	Iterator operator++() {
	  if (this->current != nullptr) {
		this->current = this->current->next;
	  }
	  return *this;
	}

	Iterator operator++(int) {
	  ++(*this);
	  return *this;
	}

	value_type operator*() {
	  if (this->current == nullptr)
		throw std::out_of_range("Iterator Out of range");
	  return this->current->value;
	}
  private:
	Node* current;
};

#endif
