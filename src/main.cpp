#include <ReflectionManager.h>
#include <Shape.h>
#include <Triangle.h>
#include <iostream>
#include "MetadataCreator.h"
#include "String.h"

int main() {
  Triangle t;
  Shape* shape = new Triangle();

  for (auto& method : ReflectionManager::getMetadata(shape)->getMethods()) {
    std::cout << method.getName() << std::endl;
    method.call<void>(t);
  }
  delete shape;
  return 0;
}
