#pragma once

#include <memory>
#include "Method.h"

// clsas to represent registered member variables of a class
class Member {
 public:
  Member(const char* _name, size_t _offset)
      : m_getter(nullptr),
        m_setter(nullptr),
        m_name(_name),
        m_offset(_offset) {}

  // no setters implemented as they are not needed
  // as there is will be no member name or offset change
  const char* getName() const { return m_name; }
  size_t getOffset() const { return m_offset; }

  void setSetterMethod(const Method& _setter) {
    m_setter = std::make_shared<Method>(_setter);
  }
  void setGetterMethod(const Method& _getter) {
    m_getter = std::make_shared<Method>(_getter);
  }

  const std::shared_ptr<Method> getGetterMethod() const { return m_getter; }
  const std::shared_ptr<Method> getSetterMethod() const { return m_setter; }

 private:
  std::shared_ptr<Method> m_getter;
  std::shared_ptr<Method> m_setter;
  const char* m_name;
  size_t m_offset;
};
