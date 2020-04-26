#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <random>
#include "node.h"

constexpr int MAX_RANDOM = 1000;
constexpr int MIN_RANDOM = 0;

template<typename T>
class List {
  public:
	List() : head(nullptr), tail(nullptr), numNodes(0) {};

	List(T* arr, const std::size_t size) { }

	List(Node<T>* node) : head(node), tail(node), numNodes(1) { }

	List(const std::size_t size) { }

	virtual ~List() { }

	List(const List& rhs) { }
	List(const List&& rhs) { }

	List& operator=(const List& rhs);
	List& operator=(const List&& rhs);

	virtual T& front() = 0;
	virtual T& back() = 0;

	virtual const T& front() const = 0;
	virtual const T& back() const = 0;

	virtual void push_front(const T& value) = 0;
	virtual void push_back(const T& value) = 0;

	virtual T& pop_front() = 0;
	virtual T& pop_back() = 0;

	virtual T& operator[](const std::size_t index) = 0;

	virtual bool empty() const = 0;

	virtual std::size_t size() const = 0;

	virtual void clear() = 0;

	virtual void erase(Node<T>* node) = 0;

	virtual void insert(Node<T>* node, const T& value) = 0;

	virtual void remove(const T& value) = 0;

	virtual void sort() = 0;

	virtual void reverse() = 0;

  protected:
	Node<T>* head;
	Node<T>* tail;
	std::size_t numNodes;
};

#endif
