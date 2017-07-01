#pragma once

#include <type_traits>

// remove const, volatile and &, &&, *, ** from type
template <typename T>
using remove_qualifiers_t = std::decay_t<T>;

// this macro generates a template class that is used to check
// if a certian class contains a function with the name functionName or not
// to use it : has_functionName_v<ClassName>;
#define HAS_FUNCTION(functionName)                                     \
  template <typename T>                                                \
  struct has_##functionName {                                          \
   private:                                                            \
    template <typename C>                                              \
    static short test(decltype(&C::functionName));                     \
    template <typename C>                                              \
    static int test(...);                                              \
                                                                       \
   public:                                                             \
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(short); \
  };                                                                   \
  template <typename T>                                                \
  constexpr bool has_##functionName##_v = has_##functionName<T>::value;

// this is a heler class to be used to call a certain function
// only if it exists in the input class
#define CALL_FUNCTION(functionName)                \
  template <typename T, bool has_function>         \
  struct call_##functionName {                     \
    static void call() {                           \
      if                                           \
        constexpr(has_function) T::functionName(); \
    }                                              \
  };

HAS_FUNCTION(defineProperties);
HAS_FUNCTION(defineMethods);

CALL_FUNCTION(defineProperties);
CALL_FUNCTION(defineMethods);
