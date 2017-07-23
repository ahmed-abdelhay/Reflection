#pragma once

#include <cstring>
#include <initializer_list>
#include <vector>
#include "Member.h"
#include "Method.h"

// class to represent metadata of a certian class
// the metadata is the class name, size, pointer to the meta data of the
// class parent and a list of the registered methods and members
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

  const Member& getMember(const std::string& _memberName) {
    auto itr = std::find_if(
        m_members.begin(), m_members.end(), [&](const auto& member) {
          return strcmp(_memberName.c_str(), member.getName()) == 0;
        });
    if (itr == m_members.end())
      throw std::invalid_argument("member name not found");
    return *itr;
  }

  const Method& getMethod(const std::string& _methodName) {
    auto itr = std::find_if(
        m_methods.begin(), m_methods.end(), [&](const auto& method) {
          return strcmp(_methodName.c_str(), method.getName()) == 0;
        });
    if (itr == m_methods.end())
      throw std::invalid_argument("method name not found");
    return *itr;
  }

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
