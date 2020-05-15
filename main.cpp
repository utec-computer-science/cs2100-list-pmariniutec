#include <iostream>
#include "list.h"
#include "node.h"

int main() {

  List<ForwardNode<int>> fl{10};

  std::cout << "Initial List: " << fl << "\n\n";

  std::cout << "Normal for loop: ";
  for (auto it = fl.begin(); it != fl.end(); it++) {
	std::cout << *it << ' ';
  }
  std::cout << '\n';

  std::cout << "Range-based for loop: ";
  for (const auto& val : fl) {
	std::cout << val << ' ';
  }
  std::cout << "\n\n";

  fl.reverse();
  std::cout << "Reversed: " << fl << '\n';

  fl.sort();
  std::cout << "Sorted: " << fl << '\n';

  fl.push_back(20);

  std::cout << fl << '\n';

  List<DoubleNode<int>> dl;

  dl.push_back(20);
  dl.push_back(30);
  dl.push_front(9000);
  dl.push_front(10);
  dl.push_back(90);
  dl.push_front(200);
  dl.push_back(210);

  std::cout << dl << '\n';

  dl.reverse();
  std::cout << dl << '\n';

  dl.sort();
  std::cout << dl << '\n';

}
