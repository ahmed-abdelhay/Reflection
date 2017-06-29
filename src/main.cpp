#include <ReflectionManager.h>
#include <Shape.h>
#include <Triangle.h>
#include <iostream>
#include "MetadataCreator.h"
#include "String.h"

int main() {
  std::cout << ReflectionManager::getClassName<Triangle>() << std::endl;
  std::cout << ReflectionManager::getClassSize<Triangle>() << std::endl;

  for (auto member : ReflectionManager::getMetadata<Triangle>()->getMembers()) {
    std::cout << member.getName() << std::endl;
    std::cout << member.getOffset() << std::endl;
  }

  Triangle t;
  for (auto& method :
       ReflectionManager::getMetadata<Triangle>()->getMethods()) {
    std::cout << method.getName() << std::endl;
    method.call<void>(t);
  }
  return 0;
}
