#pragma once

#include <iostream>
#include "Shape.h"

class Triangle : public Shape {
  REFLECT_POLYMORPHIC_CLASS(Triangle, Shape);

  PROPERTIES_BEGIN
  PROPERTY(length, GETTER(draw))
  PROPERTIES_END

  METHODS_BEGIN
  METHOD(draw)
  METHOD(draw2)
  METHODS_END

 public:
  void draw() { std::cout << "Triangle::draw()" << std::endl; }
  void draw2() { std::cout << "Triangle::draw2()" << std::endl; }

  int length;
};
