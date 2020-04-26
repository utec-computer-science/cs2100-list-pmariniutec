#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
#include "iterators/forward_iterator.h"
#include <stdexcept>
#include "list.h"

template<typename T>
class ForwardList : public List<T> {
  public:
	using iterator = ForwardIterator<T>;
	using const_iterator = ForwardIterator<const T>;

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
	  std::uniform_int_distribution<int> dist(MIN_RANDOM, MAX_RANDOM);

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
	  auto current = rhs.head;
	  auto thisCurrent = new Node<T>(current->value);
	  this->head = thisCurrent;

	  while (current->next != nullptr) {
		current = current->next;
		thisCurrent->next = new Node<T>(current->value);	
		thisCurrent = thisCurrent->next;
	  }

	  this->tail = thisCurrent;
	}

	ForwardList(const ForwardList&& rhs) {
	  auto current = rhs.head;
	  auto thisCurrent = new Node<T>(current->value);
	  this->head = thisCurrent;

	  while (current->next != nullptr) {
		auto tmp = current;
		current = current->next;
		thisCurrent->next = new Node<T>(current->value);	
		thisCurrent = thisCurrent->next;
		delete tmp;
	  }

	  this->numNodes = rhs.numNodes;
	  this->tail = thisCurrent;

	  rhs.numNodes = 0;
	  rhs.head = nullptr;
	  rhs.tail = nullptr;
	}

	ForwardList& operator=(const ForwardList& rhs) {
	  if (&rhs == this)
		return *this;

	  auto current = rhs.head;
	  auto thisCurrent = new Node<T>(current->value);
	  this->head = thisCurrent;

	  while (current->next != nullptr) {
		current = current->next;
		thisCurrent->next = new Node<T>(current->value);	
		thisCurrent = thisCurrent->next;
	  }

	  this->tail = thisCurrent;

	  return *this;
	}

	ForwardList& operator=(const ForwardList&& rhs) {
	  if (&rhs == this)
		return *this;

	  auto current = rhs.head;
	  auto thisCurrent = new Node<T>(current->value);
	  this->head = thisCurrent;

	  while (current->next != nullptr) {
		auto tmp = current;
		current = current->next;
		thisCurrent->next = new Node<T>(current->value);	
		thisCurrent = thisCurrent->next;
		delete tmp;
	  }

	  this->numNodes = rhs.numNodes;
	  this->tail = thisCurrent;

	  rhs.numNodes = 0;
	  rhs.head = nullptr;
	  rhs.tail = nullptr;

	  return *this;
	}

	T& front() override {
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->head->value;
	}

	T& back() override {
	  if (this->tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return this->tail->value;
	}

	const T& front() const override {
	  if (this->head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return this->head->value;
	}

	const T& back() const override {
	  if (this->tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return this->tail->value;
	}

	void push_front(const T& value) override {
	  auto node = new Node<T>(value);
	  if (this->head != nullptr) {
		this->head->next = node;
		this->head = node;
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

	T& pop_front() override {
	  auto top = this->head;
	  this->head = top->next;
	  this->numNodes--;
	  return top->value;
	}

	T& pop_back() override {
	  if (empty()) {
		std::out_of_range("List is empty");
	  } else if (this->numNodes == 1) {
		auto bottom = this->tail;
		this->head = this->tail = nullptr;
		this->numNodes--;
		return bottom->value;
	  }

	  auto tmp = this->head;
	  while (tmp->next->next != nullptr) {
		tmp = tmp->next;
	  }
	  this->tail = tmp;
	  auto bottom = this->tail->next;
	  this->numNodes--;
	  return bottom->value;
	}

	T& operator[](const size_t index) override {
	  if (index > this->numNodes)
		std::out_of_range("Index greater than size.");

	  auto curr = this->head;
	  for (size_t i = 0; i < index; ++i) {
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
	  if (empty())
		return;

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

	void sort() override {
	  bubbleSort();   
	}

	void reverse() override {
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

	void merge(ForwardList<T> fl) {
	  if (this->head == nullptr) {
		this->head = fl.head;
		this->tail = fl.tail;
	  } else {
		this->tail->next = fl.head;
	  }

	  this->numNodes += fl.numNodes;
	}

	void erase(Node<T>* node) override {

	}

	void insert(Node<T>* node, const T& value) override {

	}

	void remove(const T& value) override {

	}

	inline friend std::ostream& operator<<(std::ostream& o, const ForwardList<T>& fl) {
	  auto current = fl.head;
	  while (current != nullptr) {
		o << current->value << ' ';
		current = current->next;
	  }
	  return o;
	}

	iterator begin() {
	  return { this->head };
	}

	iterator end() {
	  return { this->tail->next };
	}

	const_iterator cbegin() {
	  return { this->head };
	}

	const_iterator cend() {
	  return { this->tail->next };
	}

  private:
	void bubbleSort() {
	  bool swapped;
	  Node<T>* curr;
	  Node<T>* lptr = nullptr;

	  if (this->head == NULL)
		return;

	  do {
		swapped = true;
		curr = this->head;

		while (curr->next != lptr) {
		  if (curr->value > curr->next->value) {
			std::swap(curr->value, curr->next->value);
			swapped = false;
		  }
		  curr = curr->next;
		}
		lptr = curr;
	  } while (swapped);
	}
};

#endif
