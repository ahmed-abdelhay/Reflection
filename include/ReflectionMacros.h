#pragma once

#include "MetaProgramming.h"
#include "MetadataCreator.h"

#define INIT_METADATA(className)                                       \
  static auto initMetadata() {                                         \
    static bool firstTime = true;                                      \
    if (firstTime) {                                                   \
      firstTime = false;                                               \
      return new Metadata(#className, sizeof(className));              \
    }                                                                  \
    call_defineProperties<Self, has_defineProperties_v<Self>>::call(); \
    call_defineMethods<Self, has_defineMethods_v<Self>>::call();       \
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
    return MetadataCreator<Self>::get();                               \
  }

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

#define PROPERTIES_BEGIN           \
 public:                           \
  static void defineProperties() { \
    auto metadata = MetadataCreator<Self>::get();

#define PROPERTY(propertyName) \
  metadata->addMember(         \
      {#propertyName,          \
       (size_t)((char*)&(((Self*)nullptr)->propertyName) - (char*)nullptr)});

#define PROPERTIES_END }

#define METHODS_BEGIN           \
 public:                        \
  static void defineMethods() { \
    auto metadata = MetadataCreator<Self>::get();

#define METHOD(methodName) \
  metadata->addMethod(         \
      {#methodName,
#define METHODS_END \
  }                 \
                    \
 private:
