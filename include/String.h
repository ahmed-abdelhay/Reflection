#pragma once

#include <string>
#include <type_traits>

// compile time string
template <char... cs>
struct String {};

template <typename T, T... cs>
constexpr String<cs...> operator""_s() {
  return {};
}

template <char... cs1, char... cs2>
constexpr auto operator+(String<cs1...>, String<cs2...>) {
  return String<cs1..., cs2...>{};
}

template <char... cs1, char... cs2>
constexpr auto operator==(String<cs1...>, String<cs2...>) {
  return std::is_same<String<cs1...>, String<cs2...>>::value;
}

// convert a compile time string to run time string
template <char... cs>
std::string convert(String<cs...> _input) {
  return {cs...};
}