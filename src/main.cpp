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

  for (auto member : ReflectionManager::getMetadata<Triangle>()->getMethods()) {
    std::cout << member.getName() << std::endl;
  }
  return 0;
}
