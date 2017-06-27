#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>
#include <iostream>
#include "Member.h"
#include "Method.h"

class Metadata {
 public:
  Metadata(const char* _name, size_t _size, const Metadata* _parent = nullptr,
           std::initializer_list<Member> _members = {},
           std::initializer_list<Method> _methods = {})
      : m_name(_name),
        m_size(_size),
        m_parent(_parent),
        m_members(_members),
        m_methods(_methods) {}

  void addMember(Member _member) { m_members.push_back(_member); }
  void addMethod(Method _method) { m_methods.push_back(_method); }

  const std::vector<Member>& getMembers() const { return m_members; }
  const std::vector<Method>& getMethods() const { return m_methods; }
  const Metadata* getParent() const { return m_parent; }
  const char* getName() const { return m_name; }
  size_t getSize() const { return m_size; }

 private:
  const char* m_name;
  size_t m_size;
  const Metadata* m_parent;
  std::vector<Member> m_members;
  std::vector<Method> m_methods;
};
