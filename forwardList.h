#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
#include "list.h"

template<typename T>
class ForwardList : public List<T> {
  public:
	ForwardList() {

	}

	ForwardList(T* arr) {

	}

	ForwardList(Node<T>* node) {

	}

	ForwardList(const std::size_t size) {

	}

	~ForwardList() override {

	}

	ForwardList(const ForwardList& rhs) {

	}

	ForwardList(const ForwardList&& rhs) {

	}

	ForwardList& operator=(const ForwardList& rhs) {
	  if (&rhs == this)
		return *this;
	  // TODO: Finish Implementation
	}

	ForwardList& operator=(const ForwardList&& rhs) {
	  if (&rhs == this)
		return *this;
	  // TODO: Finish Implementation
	}

	T front() const override {

	}
	T back() const override {

	}

	void push_back(const T& value) override {

	}
	void push_front(const T& value) override {

	}

	T& pop_back() override {

	}
	T& pop_front() override {

	}

	T& operator[](const std::size_t index) override {

	}

	bool empty() const override {

	}

	std::size_t size() const override {

	}

	std::size_t clear() override {

	}

	void erase(Node<T>* node) override {

	}

	void insert(Node<T>* node, const T& value) override {

	}

	void remove(const T& value) override {

	}

	ForwardList& sort() override {

	}

	ForwardList& reverse() override {

	}

};

#endif
