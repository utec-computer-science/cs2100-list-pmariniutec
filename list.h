#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"

template<typename T>
class List {
  public:
	List() {

	}

	List(T* arr) {

	}

	List(Node<T>* node) {

	}

	List(const std::size_t size) {

	}

	virtual ~List() {

	}

	List(const List& rhs) {

	}

	List& operator=(const List& rhs) {
	  if (&rhs == this)
		return *this;
	  // TODO: Finish Implementation
	}

	List(const List&& rhs) {

	}

	List& operator=(const List&& rhs) {
	  if (&rhs == this)
		return *this;
	  // TODO: Finish Implementation
	}

	virtual T front() const = 0;
	virtual T back() const = 0;

	void push_back(const T& value) = 0;
	void push_front(const T& value) = 0;

	T& pop_back() = 0;
	T& pop_front() = 0;

	T& operator[](const std::size_t index) = 0;

	bool empty() const = 0;

	std::size_t size() const = 0;

	std::size_t clear() = 0;

	void erase(Node<T>* node) = 0;

	void insert(Node<T>* node, const T& value) = 0;

	void remove(const T& value) = 0;

	List& sort() = 0;

	List& reverse() = 0;

	inline friend std::ostream& operator<<(std::ostream& o, const List<T>& list);

  private:
	Node<T>* head;
};

#endif
