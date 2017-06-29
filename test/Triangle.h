#pragma once

#include <iostream>
#include "Shape.h"

class Triangle : public Shape {
  REFLECT_POLYMORPHIC_CLASS(Triangle, Shape);

  PROPERTIES_BEGIN
  PROPERTY(length)
  PROPERTIES_END

  METHODS_BEGIN
  METHOD(draw)
  METHODS_END

 public:
  void draw() { std::cout << "Triangle::draw()" << std::endl; }

  int length;
};
