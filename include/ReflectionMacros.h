#pragma once

#include "MetaProgramming.h"
#include "MetadataCreator.h"

// macros to facilitate the member and methods registerations

#define INIT_METADATA(className)                                       \
  static auto initMetadata() {                                         \
    static bool firstTime = true;                                      \
    if (firstTime) {                                                   \
      firstTime = false;                                               \
      return new Metadata(#className, sizeof(className));              \
    }                                                                  \
    call_defineProperties<Self, has_defineProperties_v<Self>>::call(); \
    call_defineMethods<Self, has_defineMethods_v<Self>>::call();       \
    ReflectionManager::getInstance().registerType(                     \
        #className, MetadataCreator<Self>::get());                     \
    return MetadataCreator<Self>::get();                               \
  }

#define INIT_POLYMORPHIC_METADATA(className, parentName)               \
  static auto initMetadata() {                                         \
    static bool firstTime = true;                                      \
    if (firstTime) {                                                   \
      firstTime = false;                                               \
      return new Metadata(#className, sizeof(className),               \
                          MetadataCreator<parentName>::get());         \
    }                                                                  \
    call_defineProperties<Self, has_defineProperties_v<Self>>::call(); \
    call_defineMethods<Self, has_defineMethods_v<Self>>::call();       \
    ReflectionManager::getInstance().registerType(                     \
        #className, MetadataCreator<Self>::get());                     \
    return MetadataCreator<Self>::get();                               \
  }

// to register and generate a metadata for polymorphic class
// call this macro at the beginning og the class or the struct
#define REFLECT_POLYMORPHIC_CLASS(className, parentName) \
 public:                                                 \
  using Self = className;                                \
  INIT_POLYMORPHIC_METADATA(className, parentName)       \
                                                         \
  inline virtual Metadata* getMetadata() {               \
    return MetadataCreator<Self>::get();                 \
  }                                                      \
                                                         \
 private:

// to register and generate a metadata for non polymorphic class
// call this macro at the beginning og the class or the struct
#define REFLECT_CLASS(className)           \
 public:                                   \
  using Self = className;                  \
  INIT_METADATA(className)                 \
                                           \
  inline virtual Metadata* getMetadata() { \
    return MetadataCreator<Self>::get();   \
  }                                        \
                                           \
 private:

// to register memebres or properties use this format
// start first with PROPERTIES_BEGIN
// then call PROPERTY, then PROPERTY_END
#define PROPERTIES_BEGIN           \
 public:                           \
  static void defineProperties() { \
    auto metadata = MetadataCreator<Self>::get();

#define GETTER(methodName)                              \
  {                                                     \
    Method method{#methodName};                         \
    method.setFunction(std::mem_fn(&Self::methodName)); \
    member.setGetterMethod(method);                     \
  }

#define SETTER(methodName)                              \
  {                                                     \
    Method method{#methodName};                         \
    method.setFunction(std::mem_fn(&Self::methodName)); \
    member.setSetterMethod(method);                     \
  }

#define PROPERTY(propertyName, ...)                                           \
  {                                                                           \
    Member member{                                                            \
        #propertyName,                                                        \
        (size_t)((char*)&(((Self*)nullptr)->propertyName) - (char*)nullptr)}; \
    __VA_ARGS__                                                               \
    metadata->addMember(member);                                              \
  }

#define PROPERTIES_END }

// to register functions or methods use this format
// start first with METHODS_BEGIN
// then call METHOD, then METHODS_END
#define METHODS_BEGIN           \
 public:                        \
  static void defineMethods() { \
    auto metadata = MetadataCreator<Self>::get();

#define METHOD(methodName)                              \
  {                                                     \
    Method method{#methodName};                         \
    method.setFunction(std::mem_fn(&Self::methodName)); \
    metadata->addMethod(method);                        \
  }

#define METHODS_END \
  }                 \
                    \
 private:
