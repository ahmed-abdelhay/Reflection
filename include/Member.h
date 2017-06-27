#pragma once

class Member {
 public:
  constexpr Member(const char* _name, size_t _offset)
      : m_name(_name), m_offset(_offset) {}

  // no setters implemented as they are not needed
  // as there is will be no member name or offset change
  constexpr const char* getName() const { return m_name; }
  constexpr size_t getOffset() const { return m_offset; }

 private:
  const char* m_name;
  size_t m_offset;
};
