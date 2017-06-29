#pragma once

#include <functional>
#include <memory>
#include "Function.h"

// class to represent registered method in a given class
// it stores the function name and a pointer to the function
// and the ability to call the function through the call<returnType>()
class Method {
 public:
  Method(const char* _name) : m_name(_name) {}
  const char* getName() const { return m_name; }

  template <typename ReturnType, typename Type, typename... Params>
  void setFunction(
      const std::_Mem_fn<ReturnType (Type::*)(Params...)>& _function) {
    m_function =
        std::make_shared<Function<ReturnType, Type, Params...>>(_function);
  }

  template <typename ReturnType, typename Type, typename... Params>
  ReturnType call(Type& _object, Params... _params) const {
    if (auto function =
            std::dynamic_pointer_cast<Function<ReturnType, Type, Params...>>(
                m_function))
      return (*function)(_object, _params...);
    else
      throw std::invalid_argument("wrong parameter to the method!");
  }

 private:
  std::shared_ptr<FunctionBase> m_function;
  const char* m_name;
};
