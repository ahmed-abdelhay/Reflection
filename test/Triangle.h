#pragma once

#include "Shape.h"

class Triangle : public Shape {
  REFLECT_POLYMORPHIC_CLASS(Triangle, Shape);

  PROPERTIES_BEGIN
  PROPERTY(length)
  PROPERTIES_END

  int length;
};