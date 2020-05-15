#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <iostream>
#include <random>
#include <stdexcept>
#include <utility>

#include "iterators/iterator.h"
#include "node.h"

constexpr int MIN_RANDOM = -10000;
constexpr int MAX_RANDOM = 10000;

template<typename Node>
class List {
  public:
	using value_type = typename Node::value_type;
	using iterator = Iterator<Node>;
	using const_iterator = Iterator<const Node>;

	List() = default;

	List(value_type* arr, const std::size_t size) {
	  if (size < 0) {
		std::out_of_range("List size must be >= 0");
	  }

	  m_head = new Node(arr[0]);
	  auto current = m_head;
	  for (std::size_t i = 1; i < size; ++i) {
		auto node = new Node(arr[i]);
		current->next = node;
		current = current->next;
	  }
	  m_tail = current;
	  m_numNodes = size;
	}

	List(const std::size_t size) {
	  list_from_size_impl(size, typename NodeTraits<Node>::node_tag{});
	}

	~List() {
	  auto current = m_head;
	  while (current != nullptr) {
		auto tmp = current;
		current = current->next;
		delete tmp;
	  }
	}

	List(const List& rhs) {
	  auto current = rhs.m_head;
	  auto thisCurrent = new Node(current->value);
	  m_head = thisCurrent;

	  while (current->next != nullptr) {
		current = current->next;
		thisCurrent->next = new Node(current->value);
		thisCurrent = thisCurrent->next;
	  }

	  m_tail = thisCurrent;
	}

	List(const List&& rhs) {
	  auto current = rhs.m_head;
	  auto thisCurrent = new Node(current->value);
	  m_head = thisCurrent;

	  while (current->next != nullptr) {
		auto tmp = current;
		current = current->next;
		thisCurrent->next = new Node(current->value);
		thisCurrent = thisCurrent->next;
		delete tmp;
	  }

	  m_numNodes = rhs.m_numNodes;
	  m_tail = thisCurrent;

	  rhs.m_numNodes = 0;
	  rhs.m_head = nullptr;
	  rhs.m_tail = nullptr;
	}

	List& operator=(const List& rhs) {
	  if (&rhs == this)
		return *this;

	  auto current = rhs.m_head;
	  auto thisCurrent = new Node(current->value);
	  m_head = thisCurrent;

	  while (current->next != nullptr) {
		current = current->next;
		thisCurrent->next = new Node(current->value);
		thisCurrent = thisCurrent->next;
	  }

	  m_tail = thisCurrent;

	  return *this;
	}

	List& operator=(const List&& rhs) {
	  if (&rhs == this)
		return *this;

	  auto current = rhs.m_head;
	  auto thisCurrent = new Node(current->value);
	  m_head = thisCurrent;

	  while (current->next != nullptr) {
		auto tmp = current;
		current = current->next;
		thisCurrent->next = new Node(current->value);
		thisCurrent = thisCurrent->next;
		delete tmp;
	  }

	  m_numNodes = rhs.m_numNodes;
	  m_tail = thisCurrent;

	  rhs.m_numNodes = 0;
	  rhs.m_head = nullptr;
	  rhs.m_tail = nullptr;

	  return *this;
	}

	value_type& front() {
	  if (m_head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return m_head->value;
	}

	value_type& back() {
	  if (m_tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return m_tail->value;
	}

	const value_type& front() const {
	  if (m_head == nullptr)
		throw std::out_of_range("Head Out of range");
	  return m_head->value;
	}

	const value_type& back() const {
	  if (m_tail == nullptr)
		throw std::out_of_range("Tail Out of range");
	  return m_tail->value;
	}

	void push_front(const value_type& value) {
	  push_front_impl(value, typename NodeTraits<Node>::node_tag{});
	}

	void push_back(const value_type& value) {
	  push_back_impl(value, typename NodeTraits<Node>::node_tag{});
	}

	value_type& pop_front() {
	  auto top = m_head;
	  m_head = top->next;
	  m_numNodes--;
	  return top->value;
	}

	value_type& pop_back() {
	  if (empty()) {
		std::out_of_range("List is empty");
	  } else if (m_numNodes == 1) {
		auto bottom = m_tail;
		m_head = m_tail = nullptr;
		m_numNodes--;
		return bottom->value;
	  }

	  auto tmp = m_head;
	  while (tmp->next->next != nullptr) {
		tmp = tmp->next;
	  }
	  m_tail = tmp;
	  auto bottom = m_tail->next;
	  m_numNodes--;
	  return bottom->value;
	}

	value_type& operator[](const size_t index) {
	  if (index > m_numNodes)
		std::out_of_range("Index greater than size.");

	  auto curr = m_head;
	  for (size_t i = 0; i < index; ++i) {
		curr = curr->next;
	  }
	  return curr->value;
	}

	bool empty() const {
	  return m_numNodes <= 0;
	}

	std::size_t size() const {
	  return m_numNodes;
	}

	void clear() {
	  if (empty())
		return;

	  auto curr = m_head;
	  while (curr->next != nullptr) {
		auto tmp = curr;
		curr = curr->next;
		delete tmp;
		m_numNodes--;
	  }

	  m_head = m_tail = nullptr;
	  delete curr;
	  m_numNodes--;
	}

	void sort() {
	  bubbleSort();
	}

	void reverse() {
	  auto current = m_head;
	  Node* prev = nullptr;
	  Node* next = nullptr;

	  while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	  }

	  m_tail = m_head;
	  m_head = prev;
	}

	void merge(List li) {
	  if (m_head == nullptr) {
		m_head = li.m_head;
		m_tail = li.m_tail;
	  } else {
		m_tail->next = li.m_head;
	  }

	  m_numNodes += li.m_numNodes;
	}

	void erase(Node* node) {
	  auto curr = m_head;
	  Node last{nullptr};

	  while(curr != nullptr) {
		if (curr == node) {
		  last->next = curr->next;
		  delete curr;
		  break;
		}

		last = curr;
		curr = curr->next;
	  }
	}

	void insert(Node* node, const value_type& value) {
	  insert_impl(node, value, typename NodeTraits<Node>::node_tag{});
	}

	void remove(const value_type& value) {
	  remove_impl(value, typename NodeTraits<Node>::node_tag{});
	}

	inline friend std::ostream& operator<<(std::ostream& o, const List& li) {
	  auto current = li.m_head;
	  while (current != nullptr) {
		o << current->value << ' ';
		current = current->next;
	  }
	  return o;
	}

	iterator begin() {
	  return { m_head };
	}

	iterator end() {
	  return { m_tail->next };
	}

	const_iterator cbegin() {
	  return { m_head };
	}

	const_iterator cend() {
	  return { m_tail->next };
	}

  private:
	Node* m_head{nullptr};
	Node* m_tail{nullptr};
	std::size_t m_numNodes;

	void bubbleSort() {
	  bool swapped;
	  Node* curr;
	  Node* lptr = nullptr;

	  if (m_head == nullptr)
		return;

	  do {
		swapped = false;
		curr = m_head;

		while (curr->next != lptr) {
		  if (curr->value > curr->next->value) {
			std::swap(curr->value, curr->next->value);
			swapped = true;
		  }
		  curr = curr->next;
		}
		lptr = curr;
	  } while (swapped);
	}

	void push_back_impl(const value_type& value, forward_node_tag) {
	  auto node = new Node(value);
	  if (m_tail != nullptr) {
		m_tail->next = node;
		m_tail = node;
	  } else {
		m_head = node;
		m_tail = node;
	  }
	  m_numNodes++;
	}

	void push_back_impl(const value_type& value, double_node_tag) {
	  auto node = new Node(value);
	  if (m_tail != nullptr) {
		m_tail->next = node;
		node->prev = m_tail;
		m_tail = node;
	  } else {
		m_head = m_tail = node;
	  }
	  m_numNodes++;
	}

	void push_back_impl(const value_type& value, circular_node_tag) {

	}

	void push_back_impl(const value_type& value, circular_double_node_tag) {

	}

	void push_front_impl(const value_type& value, forward_node_tag) {
	  auto node = new Node(value);
	  if (m_head != nullptr) {
		node->next = node;
		m_head = node;
	  } else {
		m_head = node;
		m_tail = node;
	  }
	  m_numNodes++;
	}

	void push_front_impl(const value_type& value, double_node_tag) {
	  auto node = new Node(value);
	  if (m_head != nullptr) {
		node->next = m_head;
		m_head->prev = node;
		m_head = node;
	  } else {
		m_head = node;
		m_tail = node;
	  }
	  m_numNodes++;
	}

	void push_front_impl(const value_type& value, circular_node_tag) {

	}

	void push_front_impl(const value_type& value, circular_double_node_tag) {

	}

	void list_from_size_impl(const size_t size, forward_node_tag) {
	  if (size < 0) {
		std::out_of_range("List size must be >= 0");
	  }

	  std::random_device dev;
	  std::mt19937 rng(dev());
	  std::uniform_int_distribution<int> dist(MIN_RANDOM, MAX_RANDOM);

	  m_head = new Node(dist(rng));
	  auto current = m_head;
	  for (std::size_t i = 1; i < size; ++i) {
		auto node = new Node(dist(rng));
		current->next = node;
		current = current->next;
	  }
	  m_tail = current;
	  m_numNodes = size;
	}

	void list_from_size_impl(const size_t size, double_node_tag) {
	  if (size < 0) {
		std::out_of_range("List size must be >= 0");
	  }

	  std::random_device dev;
	  std::mt19937 rng(dev());
	  std::uniform_int_distribution<int> dist(MIN_RANDOM, MAX_RANDOM);

	  m_head = new Node(dist(rng));
	  Node last{nullptr};

	  auto current = m_head;
	  for (std::size_t i = 1; i < size; ++i) {
		auto node = new Node(dist(rng));
		current->next = node;
		current->prev = last;
		last = current;
		current = current->next;
	  }
	  m_tail = current;
	  m_numNodes = size;
	}

	void insert_impl(Node* node, const value_type& value, forward_node_tag) {
	  auto newNode = new Node(value);
	  auto curr = m_head;
	  Node last{nullptr};

	  while(curr != nullptr) {
		if (curr == node) {
		  last->next = newNode;
		  newNode->next = curr;
		  break;
		}

		last = curr;
		curr = curr->next;
	  }
	}

	void insert_impl(Node* node, const value_type& value, double_node_tag) {
	  auto newNode = new Node(value);
	  auto curr = m_head;
	  Node last{nullptr};

	  while(curr != nullptr) {
		if (curr == node) {
		  last->next = newNode;
		  newNode->prev = last;
		  newNode->next = curr;
		  curr->prev = newNode;
		  break;
		}

		last = curr;
		curr = curr->next;
	  }
	}

	void remove_impl(const value_type& value, forward_node_tag) {
	  auto curr = m_head;
	  Node last{nullptr};

	  while(curr != nullptr) {
		if (curr->value == value) {
		  last->next = curr->next;

		  if (curr == m_tail) {
			m_tail = last;
		  }

		  delete curr;
		  break;
		}

		last = curr;
		curr = curr->next;
	  }
	}

	void remove_impl(const value_type& value, double_node_tag) {
	  auto curr = m_head;
	  Node last{nullptr};

	  while(curr != nullptr) {
		if (curr->value == value) {
		  last->next = curr->next;
		  curr->prev = last;

		  if (curr == m_tail) {
			m_tail = last;
		  }

		  delete curr;
		  break;
		}

		last = curr;
		curr = curr->next;
	  }
	}

};

#endif
