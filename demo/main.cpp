#include <investigation.hpp>

int main() {
  Investigation Direction = Investigation("direction");
  Direction.direction();
  Direction.print(std::cout);
  Investigation Reverse = Investigation("reverse");
  Reverse.reverse();
  Reverse.print(std::cout);
  Investigation Random = Investigation("random");
  Random.random();
  Random.print(std::cout);
}