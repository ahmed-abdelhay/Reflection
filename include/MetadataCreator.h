#pragma once

#include "Metadata.h"

// a helper class to get the metadata instance of
// a certian type this class will initialize the required
// meta data upon first use once only
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
