#pragma once

#include <functional>

// a function base class to be able to store the
// methods in a container
class FunctionBase {
 public:
  virtual ~FunctionBase() = default;
};

template <typename ReturnType, typename Type, typename... Params>
class Function : public FunctionBase {
  using FunctionType = std::_Mem_fn<ReturnType (Type::*)(Params...)>;

 public:
  Function(const FunctionType& _function) : m_function(_function) {}
  ~Function() = default;

  ReturnType operator()(Type& _object, Params... _parameters) {
    return m_function(_object, _parameters...);
  }

 private:
  FunctionType m_function;
};
