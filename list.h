#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"

template<typename T>
class List {
  public:
	List() { }

	List(T* arr) { }

	List(Node<T>* node) { }

	List(const std::size_t size) { }

	virtual ~List() = 0;

	List(const List& rhs) { }
	List(const List&& rhs) { }

	List& operator=(const List& rhs);
	List& operator=(const List&& rhs);

	virtual T front() const = 0;
	virtual T back() const = 0;

	virtual void push_back(const T& value) = 0;
	virtual void push_front(const T& value) = 0;

	virtual T& pop_back() = 0;
	virtual T& pop_front() = 0;

	virtual T& operator[](const std::size_t index) = 0;

	virtual bool empty() const = 0;

	virtual std::size_t size() const = 0;

	virtual std::size_t clear() = 0;

	virtual void erase(Node<T>* node) = 0;

	virtual void insert(Node<T>* node, const T& value) = 0;

	virtual void remove(const T& value) = 0;

	virtual List& sort() = 0;

	virtual List& reverse() = 0;

	inline friend std::ostream& operator<<(std::ostream& o, const List<T>& list);

  private:
	Node<T>* head;
};

#endif
