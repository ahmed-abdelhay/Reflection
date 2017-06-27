#pragma once

class Method {
 public:
  constexpr Method(const char* _name) : m_name(_name) {}
  constexpr const char* getName() const { return m_name; }

 private:
  const char* m_name;
};
