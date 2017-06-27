#pragma once

#include "Metadata.h"

template <typename T>
struct MetadataCreator {
  static Metadata* get() {
    static Metadata* metadata = T::initMetadata();
    static bool firstTime = true;
    if (firstTime) {
      firstTime = false;
      T::initMetadata();
    }

    return metadata;
  }
};
