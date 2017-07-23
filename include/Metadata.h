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

  bool hasMember(const std::string& _memberName) const {
    return findInRangeByName(m_members.begin(), m_members.end(),
                             _memberName.c_str()) != m_members.end();
  }

  bool hasMethod(const std::string& _methodName) const {
    return findInRangeByName(m_methods.begin(), m_methods.end(),
                             _methodName.c_str()) != m_methods.end();
  }

  // throws invalid_argument exception in case the member name is not found
  const Member& getMember(const std::string& _memberName) const {
    auto itr = findInRangeByName(m_members.begin(), m_members.end(),
                                 _memberName.c_str());
    if (itr == m_members.end())
      throw std::invalid_argument("member name not found");
    return *itr;
  }

  // throws invalid_argument exception in case the method name is not found
  const Method& getMethod(const std::string& _methodName) const {
    auto itr = findInRangeByName(m_methods.begin(), m_methods.end(),
                                 _methodName.c_str());
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
  // search in a range defined by _begin and _end for item that
  // has a name == _nameToFind
  template <typename ItrType>
  ItrType findInRangeByName(const ItrType& _begin, const ItrType& _end,
                            const char* _nameToFind) const {
    return std::find_if(_begin, _end, [&](const auto& var) {
      return strcmp(_nameToFind, var.getName()) == 0;
    });
  }

  const char* m_name;
  size_t m_size;
  const Metadata* m_parent;
  std::vector<Member> m_members;
  std::vector<Method> m_methods;
};
