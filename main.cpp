#include <iostream>
#include "forwardList.h"

int main() {

  ForwardList<int> fl(15);

  std::cout << "Initial List: " << fl << "\n\n";

  auto it = fl.begin();
  std::cout << "Begin: " << *it << '\n';
  it++;
  std::cout << *it << '\n';

  // Normal loop
  std::cout << "Normal for loop: ";
  for (auto it = fl.begin(); it != fl.end(); it++) {
	std::cout << *it << ' ';
  }
  std::cout << '\n';

  // Range-based
  std::cout << "Range-based for loop: ";
  for (const auto& val : fl) {
	std::cout << val << ' ';
  }
  std::cout << "\n\n";

  fl.reverse();
  std::cout << "Reversed: " << fl << '\n';

  fl.sort();
  std::cout << "Sorted: " << fl << '\n';
}
