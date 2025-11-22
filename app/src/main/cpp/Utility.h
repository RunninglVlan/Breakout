#pragma once

#include <cassert>
#include <android/asset_manager.h>
#include <string>

class Utility {
public:
    static bool checkAndLogGlError(bool alwaysLog = false);

    static inline void assertGlError() { assert(checkAndLogGlError()); }

    /**
     * Loads a text file from the assets/ directory
     * @param assetManager Asset manager to use
     * @param path The path to the asset
     * @return the contents of the file as a string. Returns an empty string on failure.
     */
    static std::string loadStringFromAsset(AAssetManager *assetManager, const char *path);
};
