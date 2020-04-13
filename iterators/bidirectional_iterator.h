#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include <stdexcept>

#include "iterator.h"

template<typename T>
class BidirectionalIterator : public Iterator<T> {
  public:
	BidirectionalIterator() : Iterator<T>(){};
	BidirectionalIterator(Node<T>* node) : Iterator<T>(node){};

	BidirectionalIterator<T> operator=(BidirectionalIterator other) {
	  this->current = other.current;
	  return *this;
	}

	bool operator!=(BidirectionalIterator other) {
	  return this->current != other.current;
	}

	BidirectionalIterator operator++() {
	  if (this->current->next == nullptr) {
		throw std::out_of_range("Iterator out of range");
	  }
	  this->current = this->current->next;
	  return *this;
	}

	BidirectionalIterator operator--() {
	  if (this->current->prev == nullptr) {
		throw std::out_of_range("Iterator out of range");
	  }
	  this->current = this->current->prev;
	  return *this;
	}

	T operator*() override {
	  if (this->current == nullptr)
		throw std::out_of_range("Iterator Out of range");
	  return this->current->data;
	}
};

#endif
