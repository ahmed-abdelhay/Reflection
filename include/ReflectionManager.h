#pragma once

#include <string>
#include <unordered_map>

#include "MetaProgramming.h"
#include "Metadata.h"
#include "MetadataCreator.h"

// this clsas contains helper functions to use
// the framework with ease
class ReflectionManager {
 public:
  void registerType(const char* _name, Metadata* _metadata) {
    m_typeMap[_name] = _metadata;
  }

  Metadata* getMetadataByName(const char* _name) {
    if (m_typeMap.find(_name) != m_typeMap.end()) return m_typeMap[_name];
    return nullptr;
  }

  Metadata* getMetadataByName(const std::string& _name) const {
    return getMetadataByName(_name.c_str());
  }

  static ReflectionManager& getInstance() {
    static ReflectionManager manager;
    return manager;
  }

  template <typename T>
  static auto getMetadata() {
    return MetadataCreator<remove_qualifiers_t<T>>::get();
  }

  template <typename T>
  static auto getMetadata(T _object) {
    if
      constexpr(std::is_pointer<T>::value) return _object->getMetadata();
    else
      return _object.getMetadata();
  }

  template <typename T>
  static auto getClassName() {
    return MetadataCreator<remove_qualifiers_t<T>>::get()->getName();
  }

  template <typename T>
  static auto getClassSize() {
    return MetadataCreator<remove_qualifiers_t<T>>::get()->getSize();
  }

  template <typename T>
  static auto getClassParent() {
    return MetadataCreator<remove_qualifiers_t<T>>::get()->getParent();
  }

  template <typename T>
  static auto getClassName(const T& _object) {
    return getClassName<remove_qualifiers_t<T>>();
  }

  template <typename T>
  static auto getClassSize(const T& _object) {
    return getClassSize<remove_qualifiers_t<T>>();
  }

  template <typename T>
  static auto getClassParent(const T& _object) {
    return getClassParent<remove_qualifiers_t<T>>();
  }

  template <typename Base, typename Parent>
  static bool doesInheritFrom() {
    auto parentMetadata = MetadataCreator<remove_qualifiers_t<Parent>>::get();
    auto metadata = const_cast<Metadata*>(
        MetadataCreator<remove_qualifiers_t<Base>>::get());

    while (metadata && (metadata != parentMetadata)) {
      metadata = const_cast<Metadata*>(metadata->getParent());
    }
    return metadata == parentMetadata;
  }

  template <typename CastToType, typename T>
  static CastToType* dynamicCast(T* _object) {
    if (doesInheritFrom<CastToType, T>())
      return static_cast<CastToType>(_object);
    return nullptr;
  }

 private:
  std::unordered_map<const char*, Metadata*> m_typeMap;
};
