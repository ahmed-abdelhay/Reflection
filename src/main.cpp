#include <ReflectionManager.h>
#include <Shape.h>
#include <Triangle.h>
#include <iostream>
#include "MetadataCreator.h"
#include "String.h"

int main() {
  Triangle t;
  Shape* shape = new Triangle();

  ReflectionManager::getMetadata<Triangle>();
  for (auto& method : ReflectionManager::getInstance()
                          .getMetadataByName("Triangle")
                          ->getMethods()) {
    std::cout << method.getName() << std::endl;
    method.call<void>(t);
  }

  for (auto& member : ReflectionManager::getInstance()
                          .getMetadataByName("Triangle")
                          ->getMembers()) {
    std::cout << member.getName() << std::endl;
    member.getGetterMethod()->call<void>(t);
  }

  auto member = ReflectionManager::getInstance()
                    .getMetadataByName("Triangle")
                    ->getMember("length");
  std::cout << member.getName() << std::endl;

  delete shape;
  return 0;
}
