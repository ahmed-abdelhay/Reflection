#pragma once

#include <type_traits>

// remove const, volatile and &, &&, *, ** from type
template <typename T>
using remove_qualifiers_t = std::decay_t<T>;

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

#define CALL_FUNCTION(functionName)           \
  template <typename T, bool has_function>    \
  struct call_##functionName {                \
    static void call() { T::functionName(); } \
  };                                          \
  template <typename T>                       \
  struct call_##functionName<T, false> {      \
    static void call() {}                     \
  };

HAS_FUNCTION(defineProperties);
HAS_FUNCTION(defineMethods);

CALL_FUNCTION(defineProperties);
CALL_FUNCTION(defineMethods);
