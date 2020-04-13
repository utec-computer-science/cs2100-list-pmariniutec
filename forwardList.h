#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
#include "iterators/forward_iterator.h"
#include <stdexcept>
#include "list.h"

template<typename T>
class ForwardList : public List<T> {
  public:
	ForwardList() : List<T>() { }

	ForwardList(T* arr, const std::size_t size) { 
	  if (size < 0) {
		std::out_of_range("List size must be >= 0");
	  }

	  this->head = new Node<T>(arr[0]);	
	  auto current = this->head;
	  for (std::size_t i = 1; i < size; ++i) {
		auto node = new Node<T>(arr[i]); 
		current->next = node;
		current = current->next;
	  }
	  this->tail = current;
	  this->numNodes = size;
	}

	ForwardList(Node<T>* node) : List<T>(node) { }

	ForwardList(const std::size_t size) { 
	  if (size < 0) {
		std::out_of_range("List size must be >= 0");
	  }

	  std::random_device dev;
	  std::mt19937 rng(dev());
	  std::uniform_int_distribution<std::mt19937::result_type> dist(MIN_RANDOM, MAX_RANDOM);

	  this->head = new Node<T>(dist(rng));
	  auto current = this->head;
	  for (std::size_t i = 1; i < size; ++i) {
		auto node = new Node<T>(dist(rng));
		current->next = node;
		current = current->next;
	  }
	  this->tail = current;
	  this->numNodes = size;
	}

	~ForwardList() {
	  auto current = this->head;
	  while (current != nullptr) {
		auto tmp = current;
		current = current->next;
		delete tmp;
	  }
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
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->head->value;
	}

	T back() const override {
	  if (this->tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return this->tail->value;
	}

	void push_front(const T& value) override {
	  auto node = new Node<T>(value);
	  if (this->head != nullptr) {
		node->next = this->head;
		this->head = node->next;
	  } else {
		this->head = node;
		this->tail = node;
	  }
	  this->numNodes++;
	}

	void push_back(const T& value) override {
	  auto node = new Node<T>(value);
	  if (this->tail != nullptr) {
		this->tail->next = node;
		this->tail = node;
	  } else {
		this->head = node;
		this->tail = node;
	  }
	  this->numNodes++;
	}

	T pop_front() override {
	  auto tmp = this->head;
	  auto val = tmp->value;
	  this->head = tmp->next;
	  this->numNodes--;
	  delete tmp;
	  return val;
	}

	T pop_back() override {
	  T val;
	  if (empty()) {
		std::out_of_range("List is empty");
	  } else if (this->numNodes == 1) {
		val = this->tail->value;
		delete this->tail;
		this->head = this->tail = nullptr;
	  } else {
		auto tmp = this->head;
		val = tmp->value;
		while (tmp->next->next != nullptr) {
		  tmp = tmp->next;
		}
		this->tail = tmp;
		delete this->tail->next;
		this->tail->next = nullptr;
	  }
	  this->numNodes--;
	  return val;
	}

	T& operator[](const std::size_t index) override {
	  if (index > size()) {
		std::out_of_range("Index out of range");
	  }

	  auto curr = this->head;
	  for (std::size_t i = 0; i < index; ++i) {
		curr = curr->next; 
	  }
	  return curr->value;
	}

	bool empty() const override {
	  return this->numNodes <= 0;
	}

	std::size_t size() const override {
	  return this->numNodes;
	}

	void clear() override {
	  if (empty()) {
		return;
	  }

	  auto curr = this->head;
	  while (curr->next != nullptr) {
		auto tmp = curr;
		curr = curr->next;
		delete tmp;
		this->numNodes--;
	  }
	  this->head = this->tail = nullptr;
	  delete curr;
	  this->numNodes--;
	}

	void erase(Node<T>* node) override {
	  if (node == this->head) {
		auto tmp = this->head;
		this->head = tmp->next;
		delete tmp;
		return;
	  }

	  auto curr = this->head;
	  Node<T>* prev = nullptr;
	  while (curr != node) {
		curr = curr->next;
		prev = curr;
	  }
	  prev->next = curr->next;
	  delete curr;
	}

	void insert(Node<T>* node, const T& value) override {

	}

	void remove(const T& value) override {
	  if (value == this->head->value) {
		auto tmp = this->head;
		this->head = tmp->next;
		delete tmp;
		this->numNodes--;
		return;
	  }

	  auto curr = this->head;
	  Node<T>* prev = nullptr;
	  while (curr->value != value) {
		curr = curr->next;
		prev = curr;
	  }
	  prev->next = curr->next;
	  delete curr;
	  this->numNodes--;
	}

	ForwardList& sort() override {
	  bubbleSort();
	}

	ForwardList& reverse() override {
	  auto current = this->head;
	  Node<T>* prev = nullptr;
	  Node<T>* next = nullptr;

	  while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	  }

	  this->tail = this->head;
	  this->head = prev;
	}

	ForwardIterator<T> begin() {
	  return { this->head };
	}

	ForwardIterator<T> end() {
	  return { this->tail->next };
	}

	inline friend std::ostream& operator<<(std::ostream& o, const ForwardList<T>& fl) {
	  auto current = fl.head;
	  while (current != nullptr) {
		o << current->value << ' ';
		current = current->next;
	  }
	  o << '\n';
	  return o;
	}

  private:
	void bubbleSort() {
	  int swapped;
	  Node<T>* ptr1;
	  Node<T>* lptr = nullptr;

	  if (this->head == NULL)
		return;

	  do {
		swapped = 0;
		ptr1 = this->head;

		while (ptr1->next != lptr) {
		  if (ptr1->value > ptr1->next->value) {
			std::swap(ptr1->value, ptr1->next->value);
			swapped = 1;
		  }
		  ptr1 = ptr1->next;
		}
		lptr = ptr1;
	  } while (swapped);
	}

};

#endif
